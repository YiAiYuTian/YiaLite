#ifndef YIALITE_EVENT_H
#define YIALITE_EVENT_H

#include "../core/core.h"
#include "keycode.h"
#include "mouse_button.h"

namespace yialite
{

typedef void (*QuitEventCallback)(void* data);
typedef void (*KeyEventCallback)(Keycode keycode, bool repeat, bool down, Keymod keymod, void* data);
typedef void (*MouseButtonEventCallback)(MouseButton button, float x, float y, bool down, uint8_t clicks, void* data);
typedef void (*MouseWheelEventCallback)(float x, float y, float pos_x, float pos_y, void* data);
typedef void (*MouseMotionEventCallback)(float x, float y, float xrel, float yrel, uint32_t buttons, void* data);
typedef void (*WindowResizedEventCallback)(int width, int height, void* data);
typedef void (*WindowMovedEventCallback)(int x, int y, void* data);
typedef void (*WindowFocusGainedEventCallback)(void* data);
typedef void (*WindowFocusLostEventCallback)(void* data);

class DevUI;

class YIALITE_API Event
{
public:
    Event();
    ~Event();

    void onUpdate();
    
    void setGlobalData(void* data);
    void registerDevUIEvent(DevUI* devui);
    void registerQuitEventCallback(QuitEventCallback callback);
    void registerKeyEventCallback(KeyEventCallback callback);
    void registerMouseButtonEventCallback(MouseButtonEventCallback callback);
    void registerMouseWheelEventCallback(MouseWheelEventCallback callback);
    void registerMouseMotionEventCallback(MouseMotionEventCallback callback);
    void registerWindowResizedEventCallback(WindowResizedEventCallback callback);
    void registerWindowMovedEventCallback(WindowMovedEventCallback callback);
    void registerWindowFocusGainedEventCallback(WindowFocusGainedEventCallback callback);
    void registerWindowFocusLostEventCallback(WindowFocusLostEventCallback callback);
private:
    struct Impl;
    Impl* m_impl;
};

}

#endif