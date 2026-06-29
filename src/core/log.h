#ifndef YIALITE_LOG_H
#define YIALITE_LOG_H

#include "core.h"
#include "../utils/handle.h"
#include "../utils/string/yia_string.h"

#include <format>

namespace yialite
{

enum class LogLevel
{
    Trace,
    Info,
    Warn,
    Err,
    Fatal
};

YIALITE_API void set_log_level(LogLevel level);
YIALITE_API void set_logger_enabled(bool enabled);

YIALITE_API void log_impl(LogLevel level, const char* msg);

template<typename... Args>
void log(LogLevel level, std::format_string<Args...> format, Args&&... args)
{
    log_impl(level, std::format(format, std::forward<Args>(args)...).c_str());
}

}

template <>
struct std::formatter<yialite::String>
{
    template <class ParseContext>
    constexpr auto parse(ParseContext& ctx) const
    {
        return ctx.begin();
    }

    template <class FormatContext>
    auto format(const yialite::String& str, FormatContext& ctx) const
    {
        return std::format_to(ctx.out(), "{}", str.c_str());
    }
};

template<typename T, typename Tag>
struct std::formatter<yialite::Handle<T, Tag>>
{
    template <class ParseContext>
    constexpr auto parse(ParseContext& ctx) const
    {
        return ctx.begin();
    }

    template <class FormatContext>
    auto format(const yialite::Handle<T, Tag>& h, FormatContext& ctx) const
    {
        return std::format_to(ctx.out(), "{}", h.id);
    }
};

#endif