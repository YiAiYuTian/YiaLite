#ifndef YIALITE_MEMORY_POOL_H
#define YIALITE_MEMORY_POOL_H

#include "../../core/core.h"
#include "../utility.h"

namespace yialite
{

class YIALITE_API MemoryPool
{
public:
    MemoryPool();
    ~MemoryPool();

    void   init(size_t block_size, size_t block_count);
    void   shutdown();
    
    void*  allocate();
    bool   deallocate(void* ptr);
    
    size_t getBlockSize()  { return m_block_size; }
    size_t getBlockCount() { return m_block_count; }
    size_t getUsedCount()  { return m_used_count; }
    bool   isInitialized() { return is_initialized; }
public:
    MemoryPool(const MemoryPool&) = delete;
    MemoryPool& operator=(const MemoryPool&) = delete;
    MemoryPool(MemoryPool&&) = delete;
    MemoryPool& operator=(MemoryPool&&) = delete;
private:
    bool is_initialized = false;
    size_t m_block_size = 0;
    size_t m_block_count = 0;
    size_t m_used_count = 0;
    struct Impl;
    Impl* m_impl = nullptr;
};

}

#endif
