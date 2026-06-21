#ifndef YIALITE_HASH_KEY_H
#define YIALITE_HASH_KEY_H

#include "base_types.h"
#include "string/yia_string.h"

#include <cstring>

namespace yialite
{

template<typename T>
struct HashKey
{
    size_t operator()(const T& key) const = delete;
};

template<>
struct HashKey<Sint8>
{
    size_t operator()(Sint8 key) const
    {
        return static_cast<size_t>(key);
    }
};

template<>
struct HashKey<Uint8>
{
    size_t operator()(Uint8 key) const
    {
        return static_cast<size_t>(key);
    }
};

template<>
struct HashKey<Sint16>
{
    size_t operator()(Sint16 key) const
    {
        return static_cast<size_t>(key);
    }
};

template<>
struct HashKey<Uint16>
{
    size_t operator()(Uint16 key) const
    {
        return static_cast<size_t>(key);
    }
};

template<>
struct HashKey<Sint32>
{
    size_t operator()(Sint32 key) const
    {
        return static_cast<size_t>(key);
    }
};

template<>
struct HashKey<Uint32>
{
    size_t operator()(Uint32 key) const
    {
        return static_cast<size_t>(key);
    }
};

template<>
struct HashKey<Sint64>
{
    size_t operator()(Sint64 key) const
    {
        return static_cast<size_t>(key);
    }
};

template<>
struct HashKey<Uint64>
{
    size_t operator()(Uint64 key) const
    {
        return static_cast<size_t>(key);
    }
};

template<>
struct HashKey<bool>
{
    size_t operator()(bool key) const
    {
        return static_cast<size_t>(key);
    }
};

template<>
struct HashKey<float>
{
    size_t operator()(float key) const
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
    size_t operator()(double key) const
    {
        const Uint8* bytes = reinterpret_cast<const Uint8*>(&key);
        size_t hash = 14695981039346656037ULL;
        const size_t prime = 1099511628211ULL;
        for (size_t i = 0; i < sizeof(double); ++i)
        {
            hash ^= bytes[i];
            hash *= prime;
        }
        return hash;
    }
};

template<typename T>
struct HashKey<T*>
{
    size_t operator()(T* ptr) const
    {
        return reinterpret_cast<size_t>(ptr);
    }
};

template<>
struct HashKey<const char*>
{
    size_t operator()(const char* str) const
    {
        if (!str) return 0;
        size_t hash = 14695981039346656037ULL;
        const size_t prime = 1099511628211ULL;
        while (*str)
        {
            hash ^= static_cast<Uint8>(*str);
            hash *= prime;
            str++;
        }
        return hash;
    }
};

template<>
struct HashKey<yialite::String>
{
    size_t operator()(const yialite::String& str) const
    {
        return HashKey<const char*>{}(str.c_str());
    }
};

}

#endif