#ifndef YIALITE_MEMORY_POOL_H
#define YIALITE_MEMORY_POOL_H

#include <mutex>

namespace yialite
{

class MemPool
{
public:
	enum class AllocMode
	{
		MALLOC,
		ALIGNED_ALLOC
	};
public:
	MemPool() = default;
	~MemPool() = default;

	[[nodiscard]] bool init(size_t slot_count, size_t slot_size, AllocMode mode = AllocMode::MALLOC);
	void shutdown();

	[[nodiscard]] void* allocate();
	void deallocate(void* ptr);
	void reset_all_pages();

	[[nodiscard]] inline bool is_initialized() const { return m_is_initialized; }
	[[nodiscard]] inline size_t get_slot_size() const { return m_slot_size; }
	[[nodiscard]] inline size_t get_slot_count() const { return m_slot_count; }
	[[nodiscard]] inline size_t get_page_size() const { return m_slot_count * m_slot_size; }
	[[nodiscard]] inline size_t get_page_count() const { std::lock_guard<std::mutex> lock(m_mutex); return m_page_count; }
	[[nodiscard]] inline size_t get_allocated_bytes() const { std::lock_guard<std::mutex> lock(m_mutex); return m_allocated_bytes; }
public:
	MemPool(const MemPool&) = delete;
	MemPool& operator=(const MemPool&) = delete;
	MemPool(MemPool&&) = delete;
	MemPool& operator=(MemPool&&) = delete;
private:
	struct Page;
private:
	Page* create_page();
	void setup_free_list(Page* page);
	size_t align_up(size_t val, size_t align);

	void* mem_alloc();
	void mem_free(void* ptr);
private:

	Page* m_page_list = nullptr;
	size_t m_slot_size = 0;
	size_t m_slot_count = 0;
	size_t m_page_count = 0;
	size_t m_allocated_bytes = 0;
	AllocMode m_alloc_mode = AllocMode::MALLOC;
	mutable std::mutex m_mutex;

	bool m_is_initialized = false;
};

}

#endif