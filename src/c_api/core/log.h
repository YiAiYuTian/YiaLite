#ifndef C_YIALITE_LOG_H
#define C_YIALITE_LOG_H

#include "../../cpp_api/core/core.h"

#include <stdbool.h>

typedef enum YiaLite_LogLevel
{
    YiaLite_Log_Trace,
    YiaLite_Log_Info,
    YiaLite_Log_Warn,
    YiaLite_Log_Err,
    YiaLite_Log_Fatal
} YiaLite_LogLevel;

#ifdef __cplusplus
extern "C" {
#endif

YIALITE_API void YiaLite_SetLogLevel(YiaLite_LogLevel level);
YIALITE_API void YiaLite_SetLoggerEnabled(bool enabled);

#ifdef __cplusplus
}
#endif

#endif