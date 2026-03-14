#ifndef C_YIALITE_CONTEXT_H
#define C_YIALITE_CONTEXT_H

#include "../../src/core/core.h"

#include <stdbool.h>

typedef struct YiaLite_Window YiaLite_Window;
typedef struct YiaLite_WindowConfig YiaLite_WindowConfig;
typedef struct YiaLite_Renderer YiaLite_Renderer;
typedef struct YiaLite_Event YiaLite_Event;
typedef struct YiaLite_DevUI YiaLite_DevUI;

typedef struct YiaLite_Context {
    YiaLite_Window* window;
    YiaLite_Renderer* renderer;
    YiaLite_DevUI* devui;
    YiaLite_Event* event;
} YiaLite_Context;

#ifdef __cplusplus
extern "C" {
#endif

YIALITE_API YiaLite_Context* YiaLite_InitContext(const YiaLite_WindowConfig* config, bool enable_devui);
YIALITE_API void YiaLite_QuitContext(YiaLite_Context* context);

#ifdef __cplusplus
}
#endif

#endif