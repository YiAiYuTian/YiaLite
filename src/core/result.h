#ifndef YIALITE_RESULT_H
#define YIALITE_RESULT_H

#include "error.h"
#include "../utils/string/yia_string_view.h"
#include "../utils/base_types.h"

#include <new>
#include <utility>

namespace yialite
{

namespace detail
{

struct EmptyTag {};
struct ErrorTag {};

} // namespace detail

template <typename T>
class Result
{
public:
    Result(const T& value) : m_has_value(true) { construct_value(value); }
    Result(T&& value) noexcept : m_has_value(true) { construct_value(std::move(value)); }

    Result(ErrorCode code) : m_has_value(false) { construct_error(code); }
    Result(ErrorCode code, const char* message) : m_has_value(false) { construct_error(code, message); }
    Result(ErrorCode code, StringView message) : m_has_value(false) { construct_error(code, message.data()); }
    Result(const Error& error) : m_has_value(false) { construct_error(error); }

    Result(const Result& other) : m_has_value(other.m_has_value)
    {
        if (m_has_value)
            construct_value(other.value_ref());
        else
            construct_error(other.error_ref());
    }

    Result(Result&& other) noexcept : m_has_value(other.m_has_value)
    {
        if (m_has_value)
            construct_value(std::move(other.value_ref()));
        else
            construct_error(other.error_ref());
    }

    Result& operator=(const Result& other)
    {
        if (this != &other)
        {
            destroy();
            m_has_value = other.m_has_value;
            if (m_has_value)
                construct_value(other.value_ref());
            else
                construct_error(other.error_ref());
        }
        return *this;
    }

    Result& operator=(Result&& other) noexcept
    {
        if (this != &other)
        {
            destroy();
            m_has_value = other.m_has_value;
            if (m_has_value)
                construct_value(std::move(other.value_ref()));
            else
                construct_error(other.error_ref());
        }
        return *this;
    }

    ~Result() { destroy(); }

    bool is_ok() const noexcept { return m_has_value; }
    bool is_error() const noexcept { return !m_has_value; }
    explicit operator bool() const noexcept { return m_has_value; }
    
    T& value() & { return value_ref(); }
    const T& value() const& { return value_ref(); }
    T&& value() && { return std::move(value_ref()); }
    const T&& value() const&& { return std::move(value_ref()); }

    T* operator->() { return &value_ref(); }
    const T* operator->() const { return &value_ref(); }
    T& operator*() & { return value_ref(); }
    const T& operator*() const& { return value_ref(); }
    T&& operator*() && { return std::move(value_ref()); }

    // Error access
    const Error& error() const noexcept { return error_ref(); }
    ErrorCode error_code() const noexcept { return error_ref().code(); }

    // Value or default
    T value_or(T&& default_value) const&
    {
        return m_has_value ? value_ref() : std::move(default_value);
    }

    T value_or(T&& default_value) &&
    {
        return m_has_value ? std::move(value_ref()) : std::move(default_value);
    }

private:
    void construct_value(const T& v) { new (&m_storage) T(v); }
    void construct_value(T&& v) noexcept { new (&m_storage) T(std::move(v)); }
    void construct_error(ErrorCode code) { new (&m_error_storage) Error(code); }
    void construct_error(ErrorCode code, const char* msg) { new (&m_error_storage) Error(code, msg); }
    void construct_error(const Error& e) { new (&m_error_storage) Error(e); }

    void destroy()
    {
        if (m_has_value)
            value_ref().~T();
        else
            error_ref().~Error();
    }

    T& value_ref() { return *std::launder(reinterpret_cast<T*>(&m_storage)); }
    const T& value_ref() const { return *std::launder(reinterpret_cast<const T*>(&m_storage)); }
    Error& error_ref() { return *std::launder(reinterpret_cast<Error*>(&m_error_storage)); }
    const Error& error_ref() const { return *std::launder(reinterpret_cast<const Error*>(&m_error_storage)); }

private:
    alignas(T) Uint8 m_storage[sizeof(T)] = {};
    alignas(Error) Uint8 m_error_storage[sizeof(Error)] = {};
    bool m_has_value = false;
};

//void result
template <>
class YIALITE_API Result<void>
{
public:
    // Success
    Result() noexcept : m_has_value(true) {}
    Result(detail::EmptyTag) noexcept : m_has_value(true) {}

    // Error
    Result(ErrorCode code) : m_has_value(false) { construct_error(code); }
    Result(ErrorCode code, const char* message) : m_has_value(false) { construct_error(code, message); }
    Result(ErrorCode code, StringView message) : m_has_value(false) { construct_error(code, message.data()); }
    Result(const Error& error) : m_has_value(false) { construct_error(error); }

    Result(const Result& other) : m_has_value(other.m_has_value)
    {
        if (!m_has_value) construct_error(other.error_ref());
    }

    Result(Result&& other) noexcept : m_has_value(other.m_has_value)
    {
        if (!m_has_value) construct_error(other.error_ref());
    }

    Result& operator=(const Result& other)
    {
        if (this != &other)
        {
            destroy();
            m_has_value = other.m_has_value;
            if (!m_has_value) construct_error(other.error_ref());
        }
        return *this;
    }

    Result& operator=(Result&& other) noexcept
    {
        if (this != &other)
        {
            destroy();
            m_has_value = other.m_has_value;
            if (!m_has_value) construct_error(other.error_ref());
        }
        return *this;
    }

    ~Result() { destroy(); }

    bool is_ok() const noexcept { return m_has_value; }
    bool is_error() const noexcept { return !m_has_value; }
    explicit operator bool() const noexcept { return m_has_value; }

    const Error& error() const noexcept { return error_ref(); }
    ErrorCode error_code() const noexcept { return error_ref().code(); }

private:
    void construct_error(ErrorCode code) { new (&m_error_storage) Error(code); }
    void construct_error(ErrorCode code, const char* msg) { new (&m_error_storage) Error(code, msg); }
    void construct_error(const Error& e) { new (&m_error_storage) Error(e); }

    void destroy()
    {
        if (!m_has_value) error_ref().~Error();
    }

    Error& error_ref() { return *std::launder(reinterpret_cast<Error*>(&m_error_storage)); }
    const Error& error_ref() const { return *std::launder(reinterpret_cast<const Error*>(&m_error_storage)); }

    alignas(Error) unsigned char m_error_storage[sizeof(Error)] = {};
    bool m_has_value = false;
};

//tools
inline Result<void> ok() { return Result<void>(); }

template <typename T>
Result<T> ok_t(T&& value) { return Result<T>(std::forward<T>(value)); }

inline Result<void> err(ErrorCode code) { return Result<void>(code); }
inline Result<void> err(ErrorCode code, const char* message) { return Result<void>(code, message); }

template <typename T>
Result<T> err_t(ErrorCode code) { return Result<T>(code); }

template <typename T>
Result<T> err_t(ErrorCode code, const char* message) { return Result<T>(code, message); }

#define YIA_TRY(var, expr) \
    auto&& var##_r = (expr); \
    if (!var##_r.is_ok()) return var##_r.error(); \
    auto& var = var##_r.value()

#define YIA_TRY_VOID(expr) \
    do { \
        auto _result = (expr); \
        if (!_result.is_ok()) \
            return _result.error(); \
    } while (0)

} // namespace yialite

#endif
