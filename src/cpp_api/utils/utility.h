#ifndef YIALITE_UTILITY_H
#define YIALITE_UTILITY_H

namespace yialite
{

using nullptr_t = decltype(nullptr);

template <typename T, T Value>
struct integral_constant
{
    static constexpr T value = Value;

    using value_type = T;
    using type      = integral_constant;

    constexpr operator value_type() const noexcept { return value; }
    [[nodiscard]] constexpr value_type operator()() const noexcept { return value; }
};
template <bool Value>
using bool_constant = integral_constant<bool, Value>;

template <typename>
inline constexpr bool is_lvalue_reference_v = false;
template <typename T>
inline constexpr bool is_lvalue_reference_v<T&> = true;
template <typename T>
struct is_lvalue_reference : bool_constant<is_lvalue_reference_v<T>>{};

template <typename>
inline constexpr bool is_rvalue_reference_v = false;
template <typename T>
inline constexpr bool is_rvalue_reference_v<T&&> = true;
template <typename T>
struct is_rvalue_reference : bool_constant<is_rvalue_reference_v<T>> {};

template<typename T>
struct remove_reference { using type = T; };
template <typename T>
struct remove_reference<T&> { using type = T; };
template <typename T>
struct remove_reference<T&&> { using type = T; };
template<typename T>
using remove_reference_t = typename remove_reference<T>::type;

template <typename, typename>
inline constexpr bool is_same_v = false;
template <typename T>
inline constexpr bool is_same_v<T, T> = true;
template <typename T1, typename T2>
struct is_same : bool_constant<is_same_v<T1, T2>> {};

template <typename T>
struct remove_cv { using type = T; };
template <typename T>
struct remove_cv<const T> { using type = T; };
template <typename T>
struct remove_cv<volatile T> { using type = T; };
template <typename T>
struct remove_cv<const volatile T> { using type = T; };
template <typename T>
using remove_cv_t = typename remove_cv<T>::type;

template <typename T>
inline constexpr bool is_void_v = is_same_v<remove_cv_t<T>, void>;

template<typename T>
constexpr remove_reference_t<T>&& move(T&& arg) noexcept
{
    return static_cast<remove_reference_t<T>&&>(arg);
}

template<typename T>
constexpr T&& forward(remove_reference_t<T>& arg) noexcept
{
    return static_cast<T&&>(arg);
}

template<typename T>
constexpr T&& forward(remove_reference_t<T>&& arg) noexcept
{
    static_assert(!is_lvalue_reference_v<T>, "bad forward call");
    return static_cast<T&&>(arg);
}

}

#endif