#ifndef YIALITE_ALLOCATOR_H
#define YIALITE_ALLOCATOR_H

#include "../../core/core.h"
#include "../base_types.h"

#include <new>
#include <utility>

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
    size_t requested_size = 0;
    size_t real_size = 0;
    AllocType alloc_src = AllocType::UNKNOWN;
};

class YIALITE_API Allocator
{
public:
    static void*        allocate(size_t size, const char* file = "", int line = 0);
    static void         deallocate(void* ptr);
    static void*        reallocate(void* ptr, size_t new_size, const char* file = "", int line = 0);

    static MemoryInfo   find_memory_info(void* ptr);
    static void         print_all_memory_info();
    static size_t       get_alloc_size();
    static size_t       get_alloc_requested_size();

    static void         init();
    static void         shutdown();
};

#define ALLOCATE(type)                  static_cast<type*>(yialite::Allocator::allocate(sizeof(type), __FILE__, __LINE__))
#define ALLOCATE_SIZED(size)            yialite::Allocator::allocate(size, __FILE__, __LINE__)
#define ALLOCATE_OBJECT(type, ...)\
    []<typename ...TArgs>(TArgs&& ...args)\
    {\
        type* _p = ALLOCATE(type);\
        return new (_p) type(std::forward<TArgs>(args)...);\
    }(__VA_ARGS__)

#define DEALLOCATE(ptr)                 do{ yialite::Allocator::deallocate(ptr); ptr = nullptr; } while(0)
#define DEALLOCATE_OBJECT(type, ptr)\
    do{\
        if(ptr){\
            using _type = type;\
            ptr->~_type();\
            yialite::Allocator::deallocate(ptr);\
        }\
    } while(0)

#define REALLOCATE_SIZED(ptr, new_size)  yialite::Allocator::reallocate(ptr, new_size, __FILE__, __LINE__)
}

#endif