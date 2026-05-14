#ifndef YIALITE_ALLOCATOR_H
#define YIALITE_ALLOCATOR_H

#include "../../core/core.h"
#include "../utility.h"

#include <new>

namespace yialite
{

enum class AllocType : int
{
    UNKNOWN = -1,
    
    MALLOC = 0,
    MEM_POOL = 1
};

struct MemoryInfo
{
    const char* file = nullptr;
    int line = 0;
    size_t size = 0;
    AllocType alloc_src = AllocType::UNKNOWN;
};

class YIALITE_API Allocator
{
public:
    static void*        allocate(size_t size, const char* file = nullptr, int line = 0);
    static void         deallocate(void* ptr);
    static void*        reallocate(void* ptr, size_t size, const char* file = nullptr, int line = 0);
    
    static MemoryInfo   findMemoryInfo(void* ptr);
    static void         printAllMemoryInfo();
    static size_t       getAllocSize();
};

#define ALLOCATE(type)                  static_cast<type*>(yialite::Allocator::allocate(sizeof(type), __FILE__, __LINE__))
#define ALLOCATE_SIZED(size)            yialite::Allocator::allocate(size, __FILE__, __LINE__)
#define ALLOCATE_OBJECT(type, ...)\
    []<typename ...Args>(Args&& ...args)\
    {\
        type* ptr = ALLOCATE(type);\
        return new (ptr) type(yialite::forward<Args>(args)...);\
    }(__VA_ARGS__)

#define DEALLOCATE(ptr)                 do{ yialite::Allocator::deallocate(ptr); ptr = nullptr; } while(0)
#define DEALLOCATE_OBJECT(type, ptr)\
    do{\
        if(ptr){\
            using ObjectType = type;\
            ptr->~ObjectType();\
            yialite::Allocator::deallocate(ptr);\
        }\
    } while(0)

#define REALLOCATE(type, ptr, size)     static_cast<type*>(yialite::Allocator::reallocate(ptr, size, __FILE__, __LINE__))
#define REALLOCATE_SIZED(ptr, size)     yialite::Allocator::reallocate(ptr, size, __FILE__, __LINE__)

#define FIND_MEMORY_INFO(ptr)           yialite::Allocator::findMemoryInfo(ptr)

}

#endif