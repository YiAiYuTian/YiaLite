#ifndef C_YIALITE_EVENT_H
#define C_YIALITE_EVENT_H

#include "../../cpp_api/core/core.h"

#include "keycode.h"
#include "mouse_button.h"

#include <stdbool.h>

typedef void (*YiaLite_QuitEventCallback)(void* data);
typedef void (*YiaLite_KeyEventCallback)(YiaLite_Keycode keycode, bool repeat, bool down, YiaLite_Keymod keymod, void* data);
typedef void (*YiaLite_MouseButtonEventCallback)(YiaLite_MouseButton button, float x, float y, bool down, uint8_t clicks, void* data);
typedef void (*YiaLite_MouseWheelEventCallback)(float x, float y, float pos_x, float pos_y, void* data);
typedef void (*YiaLite_MouseMotionEventCallback)(float x, float y, float xrel, float yrel, uint32_t buttons, void* data);
typedef void (*YiaLite_WindowResizedEventCallback)(int width, int height, void* data);
typedef void (*YiaLite_WindowMovedEventCallback)(int x, int y, void* data);
typedef void (*YiaLite_WindowFocusGainedEventCallback)(void* data);
typedef void (*YiaLite_WindowFocusLostEventCallback)(void* data);

typedef struct YiaLite_DevUI YiaLite_DevUI;

typedef struct YiaLite_Event YiaLite_Event;

#ifdef __cplusplus
extern "C" {
#endif

YIALITE_API YiaLite_Event* YiaLite_CreateEvent(void);
YIALITE_API void YiaLite_DestroyEvent(YiaLite_Event* event);

YIALITE_API void YiaLite_EventOnUpdate(YiaLite_Event* event);

YIALITE_API void YiaLite_SetEventCallbackGlobalData             (YiaLite_Event* event, void* data);
YIALITE_API void YiaLite_RegisterDevUIEvent                     (YiaLite_Event* event, YiaLite_DevUI* devui);
YIALITE_API void YiaLite_RegisterQuitEventCallback              (YiaLite_Event* event, YiaLite_QuitEventCallback callback);
YIALITE_API void YiaLite_RegisterKeyEventCallback               (YiaLite_Event* event, YiaLite_KeyEventCallback callback);
YIALITE_API void YiaLite_RegisterMouseButtonEventCallback       (YiaLite_Event* event, YiaLite_MouseButtonEventCallback callback);
YIALITE_API void YiaLite_RegisterMouseWheelEventCallback        (YiaLite_Event* event, YiaLite_MouseWheelEventCallback callback);
YIALITE_API void YiaLite_RegisterMouseMotionEventCallback       (YiaLite_Event* event, YiaLite_MouseMotionEventCallback callback);
YIALITE_API void YiaLite_RegisterWindowResizedEventCallback     (YiaLite_Event* event, YiaLite_WindowResizedEventCallback callback);
YIALITE_API void YiaLite_RegisterWindowMovedEventCallback       (YiaLite_Event* event, YiaLite_WindowMovedEventCallback callback);
YIALITE_API void YiaLite_RegisterWindowFocusGainedEventCallback (YiaLite_Event* event, YiaLite_WindowFocusGainedEventCallback callback);
YIALITE_API void YiaLite_RegisterWindowFocusLostEventCallback   (YiaLite_Event* event, YiaLite_WindowFocusLostEventCallback callback);

#ifdef __cplusplus
}
#endif

#endif