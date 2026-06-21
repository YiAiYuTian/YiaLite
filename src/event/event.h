#ifndef YIALITE_EVENT_H
#define YIALITE_EVENT_H

#include "../core/core.h"
#include "keycode.h"
#include "mouse_button.h"
#include "../core/result.h"
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
    ~Event();
    Event(const Event&) = delete;
    Event& operator=(const Event&) = delete;

    static Result<Event*> create();
    static void destroy(Event* event);

    void on_update();

    void register_devui_event(DevUI* devui);
    void register_quit_event_callback(QuitEventCallback&& callback);
    void register_key_event_callback(KeyEventCallback&& callback);
    void register_mouse_button_event_callback(MouseButtonEventCallback&& callback);
    void register_mouse_wheel_event_callback(MouseWheelEventCallback&& callback);
    void register_mouse_motion_event_callback(MouseMotionEventCallback&& callback);
    void register_window_resized_event_callback(WindowResizedEventCallback&& callback);
    void register_window_moved_event_callback(WindowMovedEventCallback&& callback);
    void register_window_focus_gained_event_callback(WindowFocusGainedEventCallback&& callback);
    void register_window_focus_lost_event_callback(WindowFocusLostEventCallback&& callback);
private:
    Event() = default;
    struct Impl;
    Impl* m_impl = nullptr;
};

}

#endif
