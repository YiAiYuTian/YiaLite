#include "allocator.h"
#include "memory_pool.h"
#include "../../core/logger.h"
#include "../singleton.h"

#include <unordered_map>
#include <mutex>

namespace yialite
{

static const char* allocTypeToString(AllocType type)
{
    switch (type)
    {
    case AllocType::MALLOC:     return "malloc";
    case AllocType::MEM_POOL:   return "memory_pool";
    default:                    return "unknown";
    }
}

class MemoryTracker : public Singleton<MemoryTracker>
{
    YIALITE_SINGLETON(MemoryTracker);
public:
    void initMemPool()
    {
        m_pool_16.init(16, 256);
        m_pool_32.init(32, 256);
        m_pool_64.init(64, 128);
        m_pool_128.init(128, 64);
        m_pool_256.init(256, 32);

        is_initialized = true;
    }

    void shutdownMemPool()
    {
        m_pool_16.shutdown();
        m_pool_32.shutdown();
        m_pool_64.shutdown();
        m_pool_128.shutdown();
        m_pool_256.shutdown();

        is_initialized = false;
    }

    void* allocate(size_t size, const char* file = nullptr, int line = 0)
    {
        if (size == 0)
        {
            Logger::warn("Trying to allocate zero size memory, file: {}, line: {}", file, line);
            return nullptr;
        }

        void* ptr = nullptr;
        size_t real_size = size;
        AllocType type = AllocType::MALLOC;

        if(is_initialized)
        {
            if(size <= 16)
            {
                ptr = m_pool_16.allocate();
                real_size = 16;
                type = AllocType::MEM_POOL;
            }
            else if(size <= 32)
            {
                ptr = m_pool_32.allocate();
                real_size = 32;
                type = AllocType::MEM_POOL;
            }
            else if(size <= 64)
            {
                ptr = m_pool_64.allocate();
                real_size = 64;
                type = AllocType::MEM_POOL;
            }
            else if(size <= 128)
            {
                ptr = m_pool_128.allocate();
                real_size = 128;
                type = AllocType::MEM_POOL;
            }
            else if(size <= 256)
            {
                ptr = m_pool_256.allocate();
                real_size = 256;
                type = AllocType::MEM_POOL;
            }
        }

        //malloc
        if(!ptr)
        {
            ptr = malloc(size);
            if(!ptr) return nullptr;
        }

        {
            std::lock_guard<std::mutex> lock(m_map_mtx);
            m_tracker_map.emplace(ptr, MemoryInfo{ file, line, real_size , type });
            m_alloc_size += real_size;
        }
        return ptr;
    }

    void deallocate(void* ptr)
    {
        if(!ptr) return;

        MemoryInfo info;
        {
            std::lock_guard<std::mutex> lock(m_map_mtx);
            auto it = m_tracker_map.find(ptr);
            if (it == m_tracker_map.end()) 
            {
                Logger::warn("Trying to deallocate memory that was not allocated by this allocator");
                return;
            }
            info = it->second;

            m_alloc_size -= info.size;
            m_tracker_map.erase(it);
        }

        bool is_in_pool = false;
        if(is_initialized) is_in_pool = deallocInPoolByInfo(info, ptr);
        if(!is_in_pool) free(ptr);
    }

    void* reallocate(void* ptr, size_t size, const char* file = nullptr, int line = 0)
    {
        if(!ptr) return allocate(size, file, line);

        MemoryInfo old_info;
        bool found = false;
        {
            std::lock_guard<std::mutex> lock(m_map_mtx);
            
            if (auto it = m_tracker_map.find(ptr); it != m_tracker_map.end())
            {
                old_info = it->second;
                found = true;
            }
        }

        if (!found)
        {
            Logger::warn("Trying to reallocate memory that was not allocated by this allocator");
            return nullptr;
        }

        size_t old_size = old_info.size;
        bool is_in_pool = (old_info.alloc_src == AllocType::MEM_POOL);
        if(is_in_pool && is_initialized)
        {
            void* new_ptr = allocate(size, file, line);
            if (new_ptr) memcpy(new_ptr, ptr, std::min(old_size, size));
            else return nullptr;
            
            {
                std::lock_guard<std::mutex> lock(m_map_mtx);
                m_tracker_map.erase(ptr);
                m_alloc_size -= old_size;
            }
            
            deallocInPoolByInfo(old_info, ptr);
            return new_ptr;
        }

        void* new_ptr = realloc(ptr, size);
        if(!new_ptr) return nullptr;
        
        {
            std::lock_guard<std::mutex> lock(m_map_mtx);
            if (auto it = m_tracker_map.find(ptr); it != m_tracker_map.end())
            {
                if(new_ptr == ptr)
                {
                    it->second.size = size;
                    it->second.file = file;
                    it->second.line = line;
                }
                else
                {
                    m_tracker_map.erase(it);
                    m_tracker_map.emplace(new_ptr, MemoryInfo{ file, line, size , AllocType::MALLOC});
                }
            }
            m_alloc_size += size - old_size;
        }
        return new_ptr;
    }

    MemoryInfo findMemoryInfo(void* ptr)
    {
        if(!ptr) return MemoryInfo{ nullptr, 0, 0, AllocType::UNKNOWN};

        if(auto it = m_tracker_map.find(ptr); it != m_tracker_map.end())
        {
            return it->second;
        }
        return MemoryInfo{ nullptr, 0, 0 , AllocType::UNKNOWN };
    }

    void printAllMemoryInfo()
    {
#if defined(_DEBUG)
        for(auto& [ptr, info] : m_tracker_map)
        {
            Logger::trace("ptr: {}, size: {}, alloc_src: {}, file: {}, line: {}", 
                ptr, 
                info.size, 
                allocTypeToString(info.alloc_src), 
                info.file, 
                info.line
            );
        }
#endif
    }

    size_t getAllocSize() { return m_alloc_size; }

    bool deallocInPoolByInfo(const MemoryInfo& info, void* ptr)
    {
        if(info.alloc_src != AllocType::MEM_POOL) return false;

        switch(info.size)
        {
            case 16:    return m_pool_16.deallocate(ptr);
            case 32:    return m_pool_32.deallocate(ptr);
            case 64:    return m_pool_64.deallocate(ptr);
            case 128:   return m_pool_128.deallocate(ptr);
            case 256:   return m_pool_256.deallocate(ptr);
            default:    return false;
        }
    }
private:
    MemoryTracker() { initMemPool();}
    ~MemoryTracker() { shutdownMemPool();}
private:
    std::unordered_map<void*, MemoryInfo> m_tracker_map;
    std::mutex m_map_mtx;
    size_t m_alloc_size = 0;
    bool is_initialized = false;
    
    MemoryPool m_pool_16;
    MemoryPool m_pool_32;
    MemoryPool m_pool_64;
    MemoryPool m_pool_128;
    MemoryPool m_pool_256;
};

// allocator implementation
void* Allocator::allocate(size_t size, const char *file, int line)
{
    return MemoryTracker::instance().allocate(size, file, line);
}

void Allocator::deallocate(void *ptr)
{
    MemoryTracker::instance().deallocate(ptr);
}

void *Allocator::reallocate(void *ptr, size_t size, const char* file, int line)
{
    return MemoryTracker::instance().reallocate(ptr, size, file, line);
}

MemoryInfo Allocator::findMemoryInfo(void *ptr)
{
    return MemoryTracker::instance().findMemoryInfo(ptr);
}

void Allocator::printAllMemoryInfo()
{
    MemoryTracker::instance().printAllMemoryInfo();
}

size_t Allocator::getAllocSize()
{
    return MemoryTracker::instance().getAllocSize();
}

}