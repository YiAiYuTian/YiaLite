#include "allocator.h"
#include "../../core/logger.h"

#include <unordered_map>

namespace yialite
{

class MemoryTracker
{
public:
    static void* allocate(size_t size, const char* file = nullptr, int line = 0)
    {
        void* ptr = malloc(size);
        if(!ptr) return nullptr;

        s_tracker_map.emplace(ptr, MemoryInfo{ file, line, size });
        s_alloc_size += size;
        return ptr;
    }

    static void deallocate(void* ptr)
    {
        if(!ptr) return;

        if(auto it = s_tracker_map.find(ptr); it != s_tracker_map.end()) 
        {
            free(ptr);
            s_alloc_size -= it->second.size;
            s_tracker_map.erase(it);
        }
        else
        {
            Logger::warn("Trying to deallocate memory that was not allocated by this allocator");
        }
    }

    static void* reallocate(void* ptr, size_t size)
    {
        if(!ptr) return allocate(size);

        void* new_ptr = nullptr;
        
        auto it = s_tracker_map.find(ptr);
        if(it == s_tracker_map.end())
        {
            new_ptr = malloc(size);
            s_tracker_map.emplace(new_ptr, MemoryInfo{ nullptr, 0, size });
            s_alloc_size += size;
            return new_ptr;
        }

        new_ptr = realloc(ptr, size);
        size_t old_size = it->second.size;
        if(new_ptr == ptr) it->second.size = size;
        else
        {
            s_tracker_map.emplace(new_ptr, MemoryInfo{ it->second.file, it->second.line, size });
            s_tracker_map.erase(it);
        }
        s_alloc_size += size - old_size;

        return new_ptr;
    }

    static MemoryInfo findMemoryInfo(void* ptr)
    {
        if(!ptr) return MemoryInfo{ nullptr, 0, 0 };

        if(auto it = s_tracker_map.find(ptr); it != s_tracker_map.end())
        {
            return it->second;
        }
        return MemoryInfo{ nullptr, 0, 0 };
    }

    static void printAllMemoryInfo()
    {
#if defined(_DEBUG)
        for(auto& [ptr, info] : s_tracker_map)
        {
            Logger::trace("ptr: {}, size: {}, file: {}, line: {}", ptr, info.size, info.file, info.line);
        }
#endif
    }

    static size_t getAllocSize() { return s_alloc_size; }
private:
    static std::unordered_map<void*, MemoryInfo> s_tracker_map;
    static size_t s_alloc_size;
};
std::unordered_map<void*, MemoryInfo> MemoryTracker::s_tracker_map;
size_t MemoryTracker::s_alloc_size = 0;

//allocator implementation
void* Allocator::allocate(size_t size, const char *file, int line)
{
    return MemoryTracker::allocate(size, file, line);
}

void Allocator::deallocate(void *ptr)
{
    MemoryTracker::deallocate(ptr);
}

void *Allocator::reallocate(void *ptr, size_t size)
{
    return MemoryTracker::reallocate(ptr, size);
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