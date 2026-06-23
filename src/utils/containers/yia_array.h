#ifndef YIALITE_ARRAY_H
#define YIALITE_ARRAY_H

#include <utility>

namespace yialite
{

template<typename T, size_t N>
class Array
{
public:
    Array() = default;
    Array(const Array&) = delete;
    Array(Array&& other) noexcept
    {
        for(size_t i = 0; i < N; ++i)
        {
            m_data[i] = std::move(other.m_data[i]);
        }
    }
    ~Array() = default;

    //operators
    Array& operator=(const Array&) = delete;
    Array& operator=(Array&& other) noexcept
    {
        if(this == &other) return *this;
        
        for(size_t i = 0; i < N; ++i)
        {
            m_data[i] = std::move(other.m_data[i]);
        }
        return *this;
    }

    T& operator[](size_t idx) noexcept
    {
        return m_data[idx];
    }
    const T& operator[](size_t idx) const noexcept
    {
        return m_data[idx];
    }

    //tools
    T* begin() noexcept             { return m_data; }
    T* end() noexcept               { return m_data + N; }
    const T* begin() const noexcept { return m_data; }
    const T* end() const noexcept   { return m_data + N; }
    [[nodiscard]] constexpr size_t size() const noexcept { return N; }
private:
    T m_data[N];
};

}

#endif