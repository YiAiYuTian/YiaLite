#ifndef YIALITE_LOG_H
#define YIALITE_LOG_H

#include "core.h"
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

YIALITE_API void setLogLevel(LogLevel level);
YIALITE_API void setLoggerEnabled(bool enabled);

YIALITE_API void logImpl(LogLevel level, const char* msg);

template<typename... Args>
void log(LogLevel level, std::format_string<Args...> format, Args&&... args)
{
    logImpl(level, std::format(format, std::forward<Args>(args)...).c_str());
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
        return std::format_to(ctx.out(), "{}", str.cStr());
    }
};

#endif