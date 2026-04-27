#ifndef YIALITE_LOG_H
#define YIALITE_LOG_H

#include "core.h"

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

#endif