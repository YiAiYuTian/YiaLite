#include "memory_pool.h"
#include "../../core/logger.h"

#include <mutex>

namespace yialite
{

struct MemoryChunk
{
    MemoryChunk* next = nullptr;
    
    void* free_list = nullptr;
    void* chunk = nullptr;
};

struct MemoryPool::Impl
{
    MemoryChunk* chunk_first = nullptr;
    MemoryChunk* chunk_end = nullptr;

    std::mutex mtx;
};

MemoryPool::MemoryPool()
{
    m_impl = new Impl();
}

MemoryPool::~MemoryPool()
{
    shutdown();
    delete m_impl;
}

void MemoryPool::init(size_t block_size, size_t block_count)
{
    m_block_size = block_size;
    m_block_count = block_count;

    MemoryChunk* chunk = (MemoryChunk*)(malloc(sizeof(MemoryChunk)));
    chunk->next = nullptr;
    chunk->chunk = malloc(block_size * block_count);
    chunk->free_list = nullptr;

    void** ptr = (void**)chunk->chunk;
    for (size_t i = 0; i < block_count - 1; ++i)
    {
        *ptr = (void*) ((uintptr_t)ptr + block_size);
        ptr = (void**)*ptr;
    }
    *ptr = nullptr;

    chunk->free_list = chunk->chunk;

    m_impl->chunk_first = chunk;
    m_impl->chunk_end = chunk;

    is_initialized = true;
}

void MemoryPool::shutdown()
{
    MemoryChunk* current = m_impl->chunk_first;

    while (current)
    {
        MemoryChunk* next = current->next;

        free(current->chunk);
        free(current);

        current = next;
    }

    m_impl->chunk_first = nullptr;
    m_impl->chunk_end   = nullptr;
    m_used_count  = 0;

    is_initialized = false;
}

void* MemoryPool::allocate()
{
    std::lock_guard<std::mutex> lock(m_impl->mtx);

    if (!m_impl->chunk_first) return nullptr;

    MemoryChunk* target = m_impl->chunk_end;

    if (!target->free_list)
    {
        MemoryChunk* new_chunk = (MemoryChunk*)malloc(sizeof(MemoryChunk));
        new_chunk->next = nullptr;
        new_chunk->chunk = malloc(m_block_size * m_block_count);
        new_chunk->free_list = nullptr;

        void** ptr = (void**)new_chunk->chunk;
        for (size_t i = 0; i < m_block_count - 1; ++i)
        {
            *ptr = (void*)((uintptr_t)ptr + m_block_size);
            ptr = (void**)*ptr;
        }
        *ptr = nullptr;

        new_chunk->free_list = new_chunk->chunk;

        m_impl->chunk_end->next = new_chunk;
        m_impl->chunk_end = new_chunk;
        target = new_chunk;
    }

    void* p = target->free_list;
    target->free_list = *(void**)p;
    ++m_used_count;

    return p;
}

bool MemoryPool::deallocate(void* ptr)
{
    std::lock_guard<std::mutex> lock(m_impl->mtx);

    if (!ptr || !m_impl->chunk_first)
    {
        Logger::warn("MemoryPool(size: {})::deallocate: Invalid pointer or not initialized", m_block_size);
        return false;
    }

    MemoryChunk* current = m_impl->chunk_first;
    uintptr_t addr = (uintptr_t)ptr;

    while (current)
    {
        uintptr_t start = (uintptr_t)current->chunk;
        uintptr_t end = start + m_block_size * m_block_count;

        if (addr >= start && addr < end)
        {
            *(void**)ptr = current->free_list;
            current->free_list = ptr;
            --m_used_count;
            return true;
        }

        current = current->next;
    }

    Logger::warn("MemoryPool(size: {})::deallocate: Pointer not found", m_block_size);
    return false;
}

}
