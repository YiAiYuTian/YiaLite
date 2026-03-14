#ifndef C_YIALITE_DEVUI_H
#define C_YIALITE_DEVUI_H

#include "../../src/core/core.h"

typedef struct YiaLite_Window YiaLite_Window;
typedef struct YiaLite_Renderer YiaLite_Renderer;

typedef struct YiaLite_DevUI YiaLite_DevUI;

#ifdef __cplusplus
extern "C" {
#endif

YIALITE_API YiaLite_DevUI* YiaLite_CreateDevUI(YiaLite_Window* window, YiaLite_Renderer* renderer);
YIALITE_API void YiaLite_DestroyDevUI(YiaLite_DevUI* devui);

YIALITE_API void YiaLite_DevUIOnUpdate(YiaLite_DevUI* devui);
YIALITE_API void YiaLite_DevUIOnRender(YiaLite_DevUI* devui);
YIALITE_API void YiaLite_DevUIText(YiaLite_DevUI* devui, const char* fmt, ...);

#ifdef __cplusplus
}
#endif

#endif