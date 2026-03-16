#ifndef C_YIALITE_WINDOW_H
#define C_YIALITE_WINDOW_H

#include "../../cpp_api/core/core.h"

#include <stdint.h>

typedef enum YiaLite_WindowFlags
{
    YiaLite_WindowFlags_None                = 0,
    YiaLite_WindowFlags_Fullscreen          = 1ULL << 0,
    YiaLite_WindowFlags_Borderless          = 1ULL << 1,
    YiaLite_WindowFlags_Resizable           = 1ULL << 2,
    YiaLite_WindowFlags_MouseGrabbed        = 1ULL << 3,
    YiaLite_WindowFlags_MouseCapture        = 1ULL << 4,
    YiaLite_WindowFlags_KeyboardGrabbed     = 1ULL << 5
} YiaLite_WindowFlags;

typedef struct YiaLite_WindowConfig
{
    const char* title;
    int width;
    int height;
    YiaLite_WindowFlags flags;
} YiaLite_WindowConfig;

typedef struct YiaLite_Window YiaLite_Window;

#ifdef __cplusplus
extern "C" {
#endif

YIALITE_API YiaLite_Window* YiaLite_CreateWindow(const YiaLite_WindowConfig* config);
YIALITE_API void YiaLite_DestroyWindow(YiaLite_Window* window);

YIALITE_API YiaLite_WindowConfig YiaLite_GetWindowConfig(YiaLite_Window* window);
YIALITE_API void YiaLite_SetWindowWidth (YiaLite_Window* window, int width);
YIALITE_API void YiaLite_SetWindowHeight(YiaLite_Window* window, int height);

#ifdef __cplusplus
}
#endif

#endif