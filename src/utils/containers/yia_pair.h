#ifndef YIALITE_PAIR_H
#define YIALITE_PAIR_H

#include <utility>
#include <type_traits>

namespace yialite
{

template<typename T, typename U>
struct Pair
{
    T first;
    U second;

    constexpr Pair() = default;

    template<typename A, typename B>
    constexpr Pair(A&& a, B&& b) 
        noexcept(std::is_nothrow_constructible_v<T, A&&> && std::is_nothrow_constructible_v<U, B&&>)
        : first(std::forward<A>(a)), second(std::forward<B>(b)) {}

    constexpr Pair(const Pair&) = default;
    constexpr Pair(Pair&&) = default;

    constexpr Pair& operator=(const Pair&) = default;
    constexpr Pair& operator=(Pair&&) = default;

    constexpr bool operator==(const Pair&) const = default;
};

}

#endif
