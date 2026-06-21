#include "mem_pool.h"
#include "../../core/logger.h"

#include <cstdlib>

namespace yialite
{

struct MemPool::Page
{
	Page* next = nullptr;
	void* free_list = nullptr;
	void* free_list_start = nullptr;
};

bool MemPool::init(size_t slot_count, size_t slot_size, AllocMode mode)
{
	std::lock_guard<std::mutex> lock(m_mutex);

	if (m_is_initialized)
	{
		Logger::warn("Memory pool is already initialized");
		return false;
	}

	if (slot_count == 0 || slot_size == 0)
	{
		Logger::error("Invalid slot count or slot size");
		return false;
	}

	constexpr size_t min_size = sizeof(void*);
	slot_size = align_up(slot_size, min_size);
	m_slot_count = slot_count;
	m_slot_size = slot_size;
	m_alloc_mode = mode;

	if (m_page_list = create_page(); !m_page_list)
	{
		Logger::error("Failed to create initial page");
		return false;
	}

	m_is_initialized = true;
	return true;
}

void MemPool::shutdown()
{
	std::lock_guard<std::mutex> lock(m_mutex);

	while (m_page_list)
	{
		Page* temp = m_page_list;

		mem_free(temp->free_list_start);
		m_page_list = temp->next;
		free(temp);
	}

	m_page_list = nullptr;
	m_slot_size = 0;
	m_slot_count = 0;
	m_page_count = 0;
	m_allocated_bytes = 0;
	m_alloc_mode = AllocMode::MALLOC;
	m_is_initialized = false;
}

void* MemPool::allocate()
{
	std::lock_guard<std::mutex> lock(m_mutex);

	if (!m_page_list)
	{
		Logger::error("Memory pool not initialized");
		return nullptr;
	}

	Page* cur = m_page_list;
	while (cur)
	{
		if (cur->free_list)
		{
			void* slot = cur->free_list;
			cur->free_list = *(reinterpret_cast<void**>(slot));
			m_allocated_bytes += m_slot_size;
			return slot;
		}

		cur = cur->next;
	}

	Page* new_page = create_page();
	if (!new_page) return nullptr;
	new_page->next = m_page_list;
	m_page_list = new_page;

	void* slot = m_page_list->free_list;
	m_page_list->free_list = *(reinterpret_cast<void**>(slot));
	m_allocated_bytes += m_slot_size;
	return slot;
}

void MemPool::deallocate(void* ptr)
{
	std::lock_guard<std::mutex> lock(m_mutex);

	if (!ptr || !m_page_list) return;

	Page* cur = m_page_list;
	const size_t page_total_bytes = m_slot_count * m_slot_size;

	while (cur)
	{
		uintptr_t begin = reinterpret_cast<uintptr_t>(cur->free_list_start);
		uintptr_t end = begin + page_total_bytes;
		uintptr_t p = reinterpret_cast<uintptr_t>(ptr);

		if (p >= begin && p < end)
		{
			void** pp = reinterpret_cast<void**>(ptr);
			*pp = cur->free_list;
			cur->free_list = ptr;
			m_allocated_bytes -= m_slot_size;
			return;
		}
		cur = cur->next;
	}
	Logger::warn("Pointer does not belong to any page in the memory pool");
}

void MemPool::reset_all_pages()
{
	std::lock_guard<std::mutex> lock(m_mutex);

	if (!m_page_list) return;

	Page* page_list_start = m_page_list;
	while (m_page_list)
	{
		m_page_list->free_list = m_page_list->free_list_start;
		setup_free_list(m_page_list);
		m_page_list = m_page_list->next;
	}
	m_page_list = page_list_start;
	m_allocated_bytes = 0;
}

MemPool::Page* MemPool::create_page()
{
	Page* new_page = static_cast<Page*>(malloc(sizeof(Page)));
	if (!new_page)
	{
		Logger::error("Failed to allocate memory for page");
		return nullptr;
	}

	new_page->free_list = mem_alloc();
	if (!new_page->free_list)
	{
		Logger::error("Failed to allocate memory for free list");
		free(new_page);
		return nullptr;
	}
	new_page->free_list_start = new_page->free_list;
	new_page->next = nullptr;
	setup_free_list(new_page);

	++m_page_count;
	return new_page;
}

void MemPool::setup_free_list(Page* page)
{
	void** current_slot = reinterpret_cast<void**>(page->free_list_start);
	for (size_t i = 1; i < m_slot_count; ++i)
	{
		uintptr_t base = reinterpret_cast<uintptr_t>(current_slot);
		*current_slot = reinterpret_cast<void*>(base + m_slot_size);
		current_slot = reinterpret_cast<void**>(*current_slot);
	}
	*current_slot = nullptr;
}

size_t MemPool::align_up(size_t val, size_t align)
{
	return ((val + align - 1) & ~(align - 1));
}

void* MemPool::mem_alloc()
{
	switch (m_alloc_mode)
	{
	case AllocMode::MALLOC:
		return malloc(m_slot_count * m_slot_size);
	case AllocMode::ALIGNED_ALLOC:
	{
		size_t align = 1;
		while (align < m_slot_size) align <<= 1;
#ifdef _WIN32
		return _aligned_malloc(m_slot_count * m_slot_size, align);
#else
		return aligned_alloc(align, m_slot_count * m_slot_size);
#endif
	}
	default:
		return nullptr;
	}
}

void MemPool::mem_free(void* ptr)
{
	switch (m_alloc_mode)
	{
	case AllocMode::MALLOC:
		free(ptr);
		break;
	case AllocMode::ALIGNED_ALLOC:
#ifdef _WIN32
		_aligned_free(ptr);
#else
		free(ptr);
#endif
		break;
	default:
		break;
	}
}

}