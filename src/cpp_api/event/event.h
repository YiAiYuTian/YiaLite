#ifndef YIALITE_EVENT_H
#define YIALITE_EVENT_H

#include "../core/core.h"
#include "keycode.h"
#include "mouse_button.h"
#include "../utils/delegate.h"

namespace yialite
{

using QuitEventCallback              = Delegate<void()>;
using KeyEventCallback               = Delegate<void(Keycode keycode, bool repeat, bool down, Keymod keymod)>;
using MouseButtonEventCallback       = Delegate<void(MouseButton button, float x, float y, bool down, Uint8 clicks)>;
using MouseWheelEventCallback        = Delegate<void(float x, float y, float pos_x, float pos_y)>;
using MouseMotionEventCallback       = Delegate<void(float x, float y, float xrel, float yrel, Uint32 buttons)>;
using WindowResizedEventCallback     = Delegate<void(int width, int height)>;
using WindowMovedEventCallback       = Delegate<void(int x, int y)>;
using WindowFocusGainedEventCallback = Delegate<void()>;
using WindowFocusLostEventCallback   = Delegate<void()>;

class DevUI;

class YIALITE_API Event
{
public:
    Event();
    ~Event();

    void onUpdate();
    
    void registerDevUIEvent(DevUI* devui);
    void registerQuitEventCallback(QuitEventCallback&& callback);
    void registerKeyEventCallback(KeyEventCallback&& callback);
    void registerMouseButtonEventCallback(MouseButtonEventCallback&& callback);
    void registerMouseWheelEventCallback(MouseWheelEventCallback&& callback);
    void registerMouseMotionEventCallback(MouseMotionEventCallback&& callback);
    void registerWindowResizedEventCallback(WindowResizedEventCallback&& callback);
    void registerWindowMovedEventCallback(WindowMovedEventCallback&& callback);
    void registerWindowFocusGainedEventCallback(WindowFocusGainedEventCallback&& callback);
    void registerWindowFocusLostEventCallback(WindowFocusLostEventCallback&& callback);
private:
    struct Impl;
    Impl* m_impl;
};

}

#endif