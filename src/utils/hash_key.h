#ifndef YIALITE_HASH_KEY_H
#define YIALITE_HASH_KEY_H

#include "base_types.h"
#include "string/yia_string.h"

#include <cstring>
#include <array>
#include <bit>

namespace yialite
{

namespace detail
{
    constexpr static size_t hash_key_hash = 14695981039346656037ULL;
    constexpr static size_t hash_key_prime = 1099511628211ULL;
}

template<typename T>
struct HashKey
{
    constexpr size_t operator()(const T& key) const noexcept = delete;
};

template<>
struct HashKey<Sint8>
{
    constexpr size_t operator()(Sint8 key) const noexcept
    {
        return static_cast<size_t>(key);
    }
};

template<>
struct HashKey<Uint8>
{
    constexpr size_t operator()(Uint8 key) const noexcept
    {
        return static_cast<size_t>(key);
    }
};

template<>
struct HashKey<Sint16>
{
    constexpr size_t operator()(Sint16 key) const noexcept
    {
        return static_cast<size_t>(key);
    }
};

template<>
struct HashKey<Uint16>
{
    constexpr size_t operator()(Uint16 key) const noexcept
    {
        return static_cast<size_t>(key);
    }
};

template<>
struct HashKey<Sint32>
{
    constexpr size_t operator()(Sint32 key) const noexcept
    {
        return static_cast<size_t>(key);
    }
};

template<>
struct HashKey<Uint32>
{
    constexpr size_t operator()(Uint32 key) const noexcept
    {
        return static_cast<size_t>(key);
    }
};

template<>
struct HashKey<Sint64>
{
    constexpr size_t operator()(Sint64 key) const noexcept
    {
        return static_cast<size_t>(key);
    }
};

template<>
struct HashKey<Uint64>
{
    constexpr size_t operator()(Uint64 key) const noexcept
    {
        return static_cast<size_t>(key);
    }
};

template<>
struct HashKey<bool>
{
    constexpr size_t operator()(bool key) const noexcept
    {
        return static_cast<size_t>(key);
    }
};

template<>
struct HashKey<float>
{
    size_t operator()(float key) const noexcept
    {
        size_t result = 0;
        static_assert(sizeof(float) <= sizeof(size_t));
        memcpy(&result, &key, sizeof(float));
        return result;
    }
};

template<>
struct HashKey<double>
{
    constexpr size_t operator()(double key) const noexcept
    {
        const auto bytes = std::bit_cast<std::array<Uint8, sizeof(double)>>(key);
        size_t hash = detail::hash_key_hash;
        for (Uint8 b : bytes)
        {
            hash ^= b;
            hash *= detail::hash_key_prime;
        }
        return hash;
    }
};

template<typename T>
struct HashKey<T*>
{
    constexpr size_t operator()(T* ptr) const noexcept
    {
        return reinterpret_cast<size_t>(ptr);
    }
};

template<>
struct HashKey<const char*>
{
    constexpr size_t operator()(const char* str) const noexcept
    {
        if (!str) return 0;
        size_t hash = detail::hash_key_hash;
        while (*str)
        {
            hash ^= static_cast<Uint8>(*str);
            hash *= detail::hash_key_prime;
            str++;
        }
        return hash;
    }
};

template<>
struct HashKey<yialite::String>
{
    size_t operator()(const yialite::String& str) const noexcept
    {
        return HashKey<const char*>{}(str.c_str());
    }
};

template<>
struct HashKey<yialite::StringView>
{
    constexpr size_t operator()(yialite::StringView str) const noexcept
    {
        if (str.empty()) return 0;

        size_t hash = detail::hash_key_hash;
        for (size_t i = 0; i < str.length(); ++i)
        {
            hash ^= static_cast<Uint8>(str[i]);
            hash *= detail::hash_key_prime;
        }
        return hash;
    }
};

}

#endif