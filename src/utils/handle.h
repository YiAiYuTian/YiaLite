#ifndef YIALITE_HANDLE_H
#define YIALITE_HANDLE_H

namespace yialite
{

template<typename T, typename Tag>
struct Handle
{
    constexpr Handle() noexcept = default;
    constexpr explicit Handle(T id_) noexcept : id(id_) {}

    T id;

    //operators
    constexpr bool operator==(const Handle& other) const noexcept
    {
        return id == other.id;
    }

    constexpr bool operator!=(const Handle& other) const noexcept
    {
        return id != other.id;
    }

    constexpr bool operator<(const Handle& other) const noexcept
    {
        return id < other.id;
    }

    constexpr bool operator>(const Handle& other) const noexcept
    {
        return id > other.id;
    }

    constexpr bool operator<=(const Handle& other) const noexcept
    {
        return id <= other.id;
    }

    constexpr bool operator>=(const Handle& other) const noexcept
    {
        return id >= other.id;
    }

    constexpr Handle& operator=(const Handle& other) noexcept
    {
        id = other.id;
        return *this;
    }

    constexpr Handle& operator=(T other) noexcept
    {
        id = other;
        return *this;
    }

    constexpr Handle& operator++() noexcept
    {
        ++id;
        return *this;
    }

    constexpr Handle operator++(int) noexcept
    {
        Handle tmp = *this;
        ++id;
        return tmp;
    }
};

}

#endif