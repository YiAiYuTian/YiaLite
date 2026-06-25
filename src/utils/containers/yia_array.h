#ifndef YIALITE_ARRAY_H
#define YIALITE_ARRAY_H

namespace yialite
{

template<typename T, size_t N>
class Array
{
public:
    Array() = default;
    ~Array() = default;
    Array(Array&&) = delete;
    Array(const Array&) = delete;

    //operators
    Array& operator=(Array&&) = delete;
    Array& operator=(const Array&) = delete;
    [[nodiscard]] T& operator[](size_t idx) noexcept { return m_data[idx]; }
    [[nodiscard]] const T& operator[](size_t idx) const noexcept { return m_data[idx]; }

    //tools
    [[nodiscard]] T* data() noexcept { return m_data; }
    [[nodiscard]] const T* data() const noexcept { return m_data; }

    T* begin() noexcept { return m_data; }
    T* end() noexcept { return m_data + N; }
    const T* begin() const noexcept { return m_data; }
    const T* end() const noexcept { return m_data + N; }

    [[nodiscard]] constexpr size_t size() const noexcept { return N; }
    [[nodiscard]] constexpr size_t max_size() const noexcept { return N; }
    [[nodiscard]] constexpr bool empty() const noexcept { return N == 0; }

    void fill(const T& value)
    {
        for (size_t i = 0; i < N; ++i)
            m_data[i] = value;
    }
private:
    T m_data[N];
};

}

#endif
