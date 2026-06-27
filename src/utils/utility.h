#ifndef YIALITE_UTILITY_H
#define YIALITE_UTILITY_H

#include "string/yia_string_view.h"

namespace yialite
{

template<typename T>
constexpr StringView get_unique_type_sig() noexcept
{
#if defined(_MSC_VER)
    constexpr StringView raw = __FUNCSIG__;
#else
    constexpr StringView raw = __PRETTY_FUNCTION__;
#endif
    return raw;
}

}

#endif