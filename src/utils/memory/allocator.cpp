#include "allocator.h"
#include "mem_pool.h"
#include "../../core/logger.h"
#include "../singleton.h"

#include <mutex>
#include <cstdlib>
#include <cstring>
#include <atomic>

namespace yialite
{

static constexpr size_t BUCKET_SIZES[] = { 64, 128, 256 };
static constexpr size_t BUCKET_COUNT = sizeof(BUCKET_SIZES) / sizeof(size_t);
static constexpr Uint8 BUCKET_MALLOC = 0xFF;
static constexpr size_t POOL_SLOT_COUNT = 256;

static Uint8 s_size_to_bucket[257];
static void build_size_table()
{
    std::memset(s_size_to_bucket, BUCKET_MALLOC, sizeof(s_size_to_bucket));
    for (size_t b = 0; b < BUCKET_COUNT; ++b)
    {
        size_t lo = (b == 0) ? 1 : BUCKET_SIZES[b - 1] + 1;
        size_t hi = BUCKET_SIZES[b];
        for (size_t s = lo; s <= hi && s <= 256; ++s)
            s_size_to_bucket[s] = static_cast<Uint8>(b);
    }
}
static inline Uint8 size_to_bucket(size_t size)
{
    if (size == 0 || size > 256) return BUCKET_MALLOC;
    return s_size_to_bucket[size];
}

struct AllocationHeader
{
    Uint8 bucket_index;
    size_t requested_size;
    size_t real_size;
#if defined(_DEBUG) || defined(YIALITE_DEBUG_ALLOC)
    const char*    file;
    int            line;
    AllocationHeader* prev;
    AllocationHeader* next;
#endif
};
static constexpr size_t ALLOCATIONHEADER_SIZE = sizeof(AllocationHeader);

static AllocationHeader* from_user_ptr(void* user_ptr)
{
    auto* hdr = reinterpret_cast<AllocationHeader*>(
        static_cast<Uint8*>(user_ptr) - ALLOCATIONHEADER_SIZE);
    return hdr;
}
static void* user_ptr(AllocationHeader* ptr)
{
    return reinterpret_cast<Uint8*>(ptr) + ALLOCATIONHEADER_SIZE;
}

class MemorySystem : public Singleton<MemorySystem>
{
    YIALITE_SINGLETON(MemorySystem);
public:
    void init()
    {
        if (m_is_initialized) return;

        build_size_table();

        for (size_t i = 0; i < BUCKET_COUNT; ++i)
        {
            if (!m_pools[i].init(POOL_SLOT_COUNT, BUCKET_SIZES[i]))
            {
                m_is_initialized = false;
				Logger::error("Failed to initialize memory pool for bucket {}, size {}", i, BUCKET_SIZES[i]);
                return;
            }
        }
        m_is_initialized = true;
    }

    void shutdown()
    {
        if (!m_is_initialized) return;

#if defined(_DEBUG) || defined(YIALITE_DEBUG_ALLOC)
        report_leaks();
#endif

        for (size_t i = 0; i < BUCKET_COUNT; ++i)
        {
            m_pools[i].shutdown();
        }
        m_is_initialized = false;
    }

    void* allocate(size_t size, const char* file, int line)
    {
        if (size == 0)
        {
            Logger::warn("Allocator: trying to allocate zero size, file: {}, line: {}", file, line);
            return nullptr;
        }

        size_t total = ALLOCATIONHEADER_SIZE + size;
        Uint8 bucket = size_to_bucket(total);
        bool use_pool = (bucket != BUCKET_MALLOC);
        size_t real_size = 0;
        void* raw = nullptr;

        if (use_pool && m_is_initialized)
        {
            raw = m_pools[bucket].allocate();
            real_size = BUCKET_SIZES[bucket];
        }

        if (!raw)
        {
            raw = std::malloc(total);
            real_size = total;

            if (!raw) return nullptr;
			bucket = BUCKET_MALLOC;
        }

        auto* hdr = static_cast<AllocationHeader*>(raw);
        hdr->bucket_index = bucket;
        hdr->real_size = real_size;
        hdr->requested_size = size;
#if defined(_DEBUG) || defined(YIALITE_DEBUG_ALLOC)
        hdr->file = file;
        hdr->line = line;
        live_list_insert(hdr);

        m_total_allocated += real_size;
        m_total_requested_alloc += size;
#endif
        return user_ptr(hdr);
    }

    void deallocate(void* ptr)
    {
        if (!ptr) return;

        auto* hdr = from_user_ptr(ptr);
#if defined(_DEBUG) || defined(YIALITE_DEBUG_ALLOC)
        m_total_allocated -= hdr->real_size;
        m_total_requested_alloc -= hdr->requested_size;
        live_list_remove(hdr);
#endif
        if (hdr->bucket_index != BUCKET_MALLOC) m_pools[hdr->bucket_index].deallocate(hdr);
        else std::free(hdr);
    }

    void* reallocate(void* ptr, size_t new_size, const char* file, int line)
    {
        if (!ptr) return allocate(new_size, file, line);
        if (new_size == 0)
        {
            deallocate(ptr);
            return nullptr;
        }

        auto* hdr = from_user_ptr(ptr);
        void* new_raw = nullptr;
        size_t real_size = hdr->real_size;
        size_t requested_size = hdr->requested_size;
        Uint8 bucket_idx = hdr->bucket_index;

        if (bucket_idx != BUCKET_MALLOC)
        {
#if defined(_DEBUG) || defined(YIALITE_DEBUG_ALLOC)
            live_list_remove(hdr);
#endif
            new_raw = allocate(new_size, file, line);
            if (!new_raw) return nullptr;
            
            std::memcpy(new_raw, ptr, new_size < hdr->requested_size ? new_size : hdr->requested_size);
            m_pools[bucket_idx].deallocate(hdr);

#if defined(_DEBUG) || defined(YIALITE_DEBUG_ALLOC)
            m_total_allocated -= real_size;
            m_total_requested_alloc -= requested_size;
#endif
            return new_raw;
        }
        else
        {
#if defined(_DEBUG) || defined(YIALITE_DEBUG_ALLOC)
            live_list_remove(hdr);
#endif
            size_t total = new_size + ALLOCATIONHEADER_SIZE;
            new_raw = std::realloc(hdr, total);
            if (!new_raw) return nullptr;

			auto* new_hdr = static_cast<AllocationHeader*>(new_raw);
            new_hdr->bucket_index = BUCKET_MALLOC;
            new_hdr->real_size = total;
            new_hdr->requested_size = new_size;
#if defined(_DEBUG) || defined(YIALITE_DEBUG_ALLOC)
            new_hdr->file = file;
            new_hdr->line = line;
            live_list_insert(new_hdr);
            m_total_allocated -= real_size - total;
            m_total_requested_alloc -= requested_size - new_size;
#endif
            return user_ptr(new_hdr);
        }
    }

    MemoryInfo find_memory_info(void* ptr)
    {
#if defined(_DEBUG) || defined(YIALITE_DEBUG_ALLOC)
        std::lock_guard<std::mutex> lock(m_live_mutex);
        
        if (!ptr) return MemoryInfo{ nullptr, 0, 0, 0, AllocType::UNKNOWN };
        
        auto* hdr = from_user_ptr(ptr);
        return MemoryInfo{
            hdr->file,
            hdr->line,
            hdr->requested_size,
            hdr->real_size,
            (hdr->bucket_index != BUCKET_MALLOC) ? AllocType::MEM_POOL : AllocType::MALLOC
        };
#endif
        return MemoryInfo{ nullptr, 0, 0, 0, AllocType::UNKNOWN };
    }

    void print_all_memory_info()
    {
#if defined(_DEBUG) || defined(YIALITE_DEBUG_ALLOC)
        std::lock_guard<std::mutex> lock(m_live_mutex);

        Logger::info("Allocator: total allocated = {} bytes(request: {} bytes)", 
            m_total_allocated.load(), m_total_requested_alloc.load());
        for (size_t i = 0; i < BUCKET_COUNT; ++i)
        {
            if (m_pools[i].is_initialized())
            {
                Logger::info("  Pool[{}](size={}) slots: allocated={} bytes, pages={}",
                    i, BUCKET_SIZES[i],
                    m_pools[i].get_allocated_bytes(),
                    m_pools[i].get_page_count());
            }
        }
#endif
    }

    size_t get_alloc_size() const 
    {
#if defined(_DEBUG) || defined(YIALITE_DEBUG_ALLOC)
        return m_total_allocated.load();
#endif
        return size_t(0);
    }

    size_t get_alloc_requested_size() const
    {
#if defined(_DEBUG) || defined(YIALITE_DEBUG_ALLOC)
        return m_total_requested_alloc.load();
#endif
        return size_t(0);
    }

private:
    MemorySystem() = default;
    ~MemorySystem() = default;

#if defined(_DEBUG) || defined(YIALITE_DEBUG_ALLOC)
    void live_list_insert(AllocationHeader* hdr)
    {
        std::lock_guard<std::mutex> lock(m_live_mutex);
        hdr->prev = nullptr;
        hdr->next = m_live_head;
        if (m_live_head) m_live_head->prev = hdr;
        m_live_head = hdr;
    }

    void live_list_remove(AllocationHeader* hdr)
    {
        std::lock_guard<std::mutex> lock(m_live_mutex);
        if (hdr->prev) hdr->prev->next = hdr->next;
        else           m_live_head = hdr->next;
        if (hdr->next) hdr->next->prev = hdr->prev;
        hdr->prev = nullptr;
        hdr->next = nullptr;
    }

    void report_leaks()
    {
        std::lock_guard<std::mutex> lock(m_live_mutex);
        if (!m_live_head) return;

        Logger::error("=== MEMORY LEAK DETECTED ===");
        size_t leak_count = 0;
        size_t leak_bytes = 0;
        size_t requested_leak_bytes = 0;
        AllocationHeader* cur = m_live_head;
        while (cur)
        {
            Logger::error("  Leak #{}: {} bytes(request: {} bytes), allocated at {}:{}",
                leak_count + 1, cur->real_size, cur->requested_size,
                cur->file ? cur->file : "unknown", cur->line);
            leak_bytes += cur->real_size;
            requested_leak_bytes += cur->requested_size;
            ++leak_count;
            cur = cur->next;
        }
        Logger::error("=== TOTAL: {} leaks, {} bytes, REQUESTED: {} bytes ===", leak_count, leak_bytes, requested_leak_bytes);
    }
#endif // _DEBUG || YIALITE_DEBUG_ALLOC

private:
    MemPool m_pools[BUCKET_COUNT];
    bool m_is_initialized = false;

#if defined(_DEBUG) || defined(YIALITE_DEBUG_ALLOC)
    std::mutex m_live_mutex;
    std::atomic<size_t> m_total_allocated{ 0 };
    std::atomic<size_t> m_total_requested_alloc{ 0 };
    AllocationHeader* m_live_head = nullptr;
#endif
};

//allocator
void* Allocator::allocate(size_t size, const char* file, int line)
{
    return MemorySystem::instance().allocate(size, file, line);
}

void Allocator::deallocate(void* ptr)
{
    MemorySystem::instance().deallocate(ptr);
}

void* Allocator::reallocate(void* ptr, size_t new_size, const char* file, int line)
{
    return MemorySystem::instance().reallocate(ptr, new_size, file, line);
}

MemoryInfo Allocator::find_memory_info(void* ptr)
{
    return MemorySystem::instance().find_memory_info(ptr);
}

void Allocator::print_all_memory_info()
{
    MemorySystem::instance().print_all_memory_info();
}

size_t Allocator::get_alloc_size()
{
    return MemorySystem::instance().get_alloc_size();
}

size_t Allocator::get_alloc_requested_size()
{
    return MemorySystem::instance().get_alloc_requested_size();
}

void Allocator::init()
{
    MemorySystem::instance().init();
}

void Allocator::shutdown()
{
    MemorySystem::instance().shutdown();
}

}
