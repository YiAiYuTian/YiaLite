#ifndef YIALITE_UTILITY_H
#define YIALITE_UTILITY_H

namespace yialite
{

template <typename T, T Value>
struct integralConstant
{
    static constexpr T value = Value;

    using ValueType = T;
    using Type      = integralConstant;

    constexpr operator ValueType() const noexcept { return value; }
    [[nodiscard]] constexpr ValueType operator()() const noexcept { return value; }
};

template <bool T>
using boolConstant = integralConstant<bool, T>;

template <typename>
inline constexpr bool isLValueReference_V = false;

template <typename T>
inline constexpr bool isLValueReference_V<T&> = true;

template <typename T>
struct isLValueReference : boolConstant<isLValueReference_V<T>>{};

template <typename>
inline constexpr bool isRValueReference_V = false;

template <typename T>
inline constexpr bool isRValueReference_V<T&&> = true;

template <typename T>
struct isRValueReference : boolConstant<isRValueReference_V<T>> {};

template<typename T>
struct RemoveReference
{
    using type = T;
};

template <typename T>
struct RemoveReference<T&> {
    using type = T;
};

template <typename T>
struct RemoveReference<T&&> {
    using type = T;
};

template<typename T>
using RemoveReference_T = typename RemoveReference<T>::type;

template<typename T>
constexpr RemoveReference_T<T>&& move(T&& arg) noexcept
{
    return static_cast<RemoveReference_T<T>&&>(arg);
}

template<typename T>
constexpr T&& forward(RemoveReference_T<T>& arg) noexcept
{
    return static_cast<T&&>(arg);
}

template<typename T>
constexpr T&& forward(RemoveReference_T<T>&& arg) noexcept
{
    static_assert(!isLValueReference_V<T>, "bad forward call");
    return static_cast<T&&>(arg);
}

}

#endif