#include "allocator.h"
#include "memory_pool.h"
#include "../../core/logger.h"

#include <unordered_map>

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

class MemoryTracker
{
public:
    static void initMemPool()
    {
        s_pool_16.init(16, 256);
        s_pool_32.init(32, 256);
        s_pool_64.init(64, 128);
        s_pool_128.init(128, 64);
        s_pool_256.init(256, 32);

        is_initialized = true;
    }

    static void resetMemPool()
    {
        s_pool_16.shutdown();
        s_pool_32.shutdown();
        s_pool_64.shutdown();
        s_pool_128.shutdown();
        s_pool_256.shutdown();

        is_initialized = false;
    }

    static void* allocate(size_t size, const char* file = nullptr, int line = 0)
    {
        if (size == 0)
        {
            Logger::warn("Trying to allocate zero size memory, file: {}, line: {}", file, line);
            return nullptr;
        }

        if(is_initialized)
        {
            if(size <= 16)
            {
                void* ptr = s_pool_16.allocate();
                s_tracker_map.emplace(ptr, MemoryInfo{ file, line, 16, AllocType::MEM_POOL });
                s_alloc_size += 16;
                return ptr;
            }
            else if(size <= 32)
            {
                void* ptr = s_pool_32.allocate();
                s_tracker_map.emplace(ptr, MemoryInfo{ file, line, 32, AllocType::MEM_POOL });
                s_alloc_size += 32;
                return ptr;
            }
            else if(size <= 64)
            {
                void* ptr = s_pool_64.allocate();
                s_tracker_map.emplace(ptr, MemoryInfo{ file, line, 64, AllocType::MEM_POOL });
                s_alloc_size += 64;
                return ptr;
            }
            else if(size <= 128)
            {
                void* ptr = s_pool_128.allocate();
                s_tracker_map.emplace(ptr, MemoryInfo{ file, line, 128, AllocType::MEM_POOL });
                s_alloc_size += 128;
                return ptr;
            }
            else if(size <= 256)
            {
                void* ptr = s_pool_256.allocate();
                s_tracker_map.emplace(ptr, MemoryInfo{ file, line, 256, AllocType::MEM_POOL });
                s_alloc_size += 256;
                return ptr;
            }
        }

        //malloc
        void* ptr = malloc(size);
        if(!ptr) return nullptr;

        s_tracker_map.emplace(ptr, MemoryInfo{ file, line, size , AllocType::MALLOC});
        s_alloc_size += size;
        return ptr;
    }

    static void deallocate(void* ptr)
    {
        if(!ptr) return;

        if(auto it = s_tracker_map.find(ptr); it != s_tracker_map.end())
        {
            bool is_in_pool = false;
            if(is_initialized) is_in_pool = deallocInPool(it);
            if(!is_in_pool) free(ptr);
            
            s_alloc_size -= it->second.size;
            s_tracker_map.erase(it);
        }
        else
        {
            Logger::warn("Trying to deallocate memory that was not allocated by this allocator");
        }
    }

    static void* reallocate(void* ptr, size_t size, const char* file = nullptr, int line = 0)
    {
        if(!ptr) return allocate(size, file, line);

        auto it = s_tracker_map.find(ptr);
        if(it != s_tracker_map.end())
        {
            bool is_in_pool = false;
            void* new_ptr = nullptr;
            size_t old_size = it->second.size;
            
            if(is_initialized) is_in_pool = deallocInPool(it);
            
            if(is_in_pool)
            {
                s_alloc_size -= old_size;
                s_tracker_map.erase(it);
                return allocate(size, file, line);
            }
            else
            {
                new_ptr = realloc(ptr, size);
                if(new_ptr == ptr)
                {
                    it->second.size = size;
                    it->second.file = file;
                    it->second.line = line;
                }
                else
                {
                    s_tracker_map.erase(it);
                    s_tracker_map.emplace(new_ptr, MemoryInfo{ file, line, size , AllocType::MALLOC});
                }
                s_alloc_size += size - old_size;
                return new_ptr;
            }
        }
        else
        {
            Logger::warn("Trying to reallocate memory that was not allocated by this allocator");
            return nullptr;
        }
    }

    static MemoryInfo findMemoryInfo(void* ptr)
    {
        if(!ptr) return MemoryInfo{ nullptr, 0, 0, AllocType::UNKNOWN};

        if(auto it = s_tracker_map.find(ptr); it != s_tracker_map.end())
        {
            return it->second;
        }
        return MemoryInfo{ nullptr, 0, 0 , AllocType::UNKNOWN };
    }

    static void printAllMemoryInfo()
    {
#if defined(_DEBUG)
        for(auto& [ptr, info] : s_tracker_map)
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

    static size_t getAllocSize() { return s_alloc_size; }

    static bool deallocInPool(std::unordered_map<void*, MemoryInfo>::iterator it)
    {
        void* ptr = it->first;
        switch(it->second.size)
        {
            case 16:    return s_pool_16.deallocate(ptr);
            case 32:    return s_pool_32.deallocate(ptr);
            case 64:    return s_pool_64.deallocate(ptr);
            case 128:   return s_pool_128.deallocate(ptr);
            case 256:   return s_pool_256.deallocate(ptr);
            default:    return false;
        }
    }
private:
    static std::unordered_map<void*, MemoryInfo> s_tracker_map;
    static size_t s_alloc_size;
    static bool is_initialized;

    static MemoryPool s_pool_16;
    static MemoryPool s_pool_32;
    static MemoryPool s_pool_64;
    static MemoryPool s_pool_128;
    static MemoryPool s_pool_256;
};
std::unordered_map<void*, MemoryInfo> MemoryTracker::s_tracker_map;
size_t MemoryTracker::s_alloc_size = 0;
bool MemoryTracker::is_initialized = false;

MemoryPool MemoryTracker::s_pool_16;
MemoryPool MemoryTracker::s_pool_32;
MemoryPool MemoryTracker::s_pool_64;
MemoryPool MemoryTracker::s_pool_128;
MemoryPool MemoryTracker::s_pool_256;

// allocator implementation
void Allocator::initMemPool()
{
    MemoryTracker::initMemPool();
}

void Allocator::resetMemPool()
{
    MemoryTracker::resetMemPool();
}

void* Allocator::allocate(size_t size, const char *file, int line)
{
    return MemoryTracker::allocate(size, file, line);
}

void Allocator::deallocate(void *ptr)
{
    MemoryTracker::deallocate(ptr);
}

void *Allocator::reallocate(void *ptr, size_t size, const char* file, int line)
{
    return MemoryTracker::reallocate(ptr, size, file, line);
}

MemoryInfo Allocator::findMemoryInfo(void *ptr)
{
    return MemoryTracker::findMemoryInfo(ptr);
}

void Allocator::printAllMemoryInfo()
{
    MemoryTracker::printAllMemoryInfo();
}

size_t Allocator::getAllocSize()
{
    return MemoryTracker::getAllocSize();
}

}