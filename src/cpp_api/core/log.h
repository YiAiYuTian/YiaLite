#ifndef YIALITE_LOG_H
#define YIALITE_LOG_H

#include "core.h"

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

YIALITE_API void log(LogLevel level, const char* format, ...);

}

#endif