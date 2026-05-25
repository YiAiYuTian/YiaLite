#ifndef YIALITE_PAIR_H
#define YIALITE_PAIR_H

#include "../utility.h"

namespace yialite 
{

template<typename T, typename U>
struct Pair
{
    T first;
    U second;

    constexpr Pair() = default;

    template<typename A, typename B>
    constexpr Pair(A&& a, B&& b) noexcept
        : first(yialite::forward<A>(a)),
          second(yialite::forward<B>(b)) {}
    constexpr Pair(const Pair&) = default;
    constexpr Pair(Pair&&) noexcept = default;

    constexpr Pair& operator=(const Pair&) = default;
    constexpr Pair& operator=(Pair&&) noexcept = default;

    constexpr bool operator==(const Pair& other) const
    {
        return first == other.first && second == other.second;
    }

    constexpr bool operator!=(const Pair& other) const
    {
        return !(*this == other);
    }
};

}

#endif