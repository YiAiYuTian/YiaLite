#ifndef YIALITE_EVENT_ABSTRACT_H
#define YIALITE_EVENT_ABSTRACT_H

#include "keycode.h"
#include "mouse_button.h"
#include "../utils/delegate.h"
#include "../utils/base_types.h"
#include "../utils/hash_key.h"
#include "../utils/utility.h"
#include "../utils/handle.h"
#include "../window/window_config.h"

namespace yialite
{

struct EventPriorityTag; 
using EventPriorityID = Handle<Uint8, EventPriorityTag>;
enum class EventPriority : Uint8
{
    UI = 0,
    GameLogic = 1,
    Background = 2,

    Max
};
inline constexpr size_t EVENT_PRIORITY_COUNT = static_cast<size_t>(EventPriority::Max);

struct EventTypeTag;
using EventTypeID = Handle<Uint64, EventTypeTag>;
class IEvent
{
public:
    virtual ~IEvent() = default;

    virtual EventTypeID get_event_type_id() const noexcept = 0;
protected:
    constexpr IEvent() noexcept = default;
public:
    mutable bool consumed = false;
};

template<typename SelfType>
class EventBase : public IEvent
{
public:
    constexpr static EventTypeID evt_t_hash = EventTypeID(HashKey<StringView>{}(get_unique_type_sig<SelfType>()));

    EventTypeID get_event_type_id() const noexcept override { return evt_t_hash; }
protected:
    constexpr EventBase() noexcept = default;
};

class QuitEvent : public EventBase<QuitEvent> {};

class KeyEvent : public EventBase<KeyEvent>
{
public:
    Keycode key;
    bool repeat;
    bool down;
    Keymod mod;
    WindowID win_id;
};

class MouseButtonEvent : public EventBase<MouseButtonEvent>
{
public:
    MouseButton btn;
    float x, y;
    bool down;
    Uint8 clicks;
    WindowID win_id;
};

class MouseWheelEvent : public EventBase<MouseWheelEvent>
{
public:
    float x, y;
    float mouse_x, mouse_y;
    WindowID win_id;
};

class MouseMotionEvent : public EventBase<MouseMotionEvent>
{
public:
    float x, y;
    float rel_x, rel_y;
    MouseButtonFlags_ btn_flags;
    WindowID win_id;
};

class WindowResizeEvent : public EventBase<WindowResizeEvent>
{
public:
    int w, h;
    WindowID win_id;
};

class WindowMovedEvent : public EventBase<WindowMovedEvent>
{
public:
    int x, y;
    WindowID win_id;
};

class WindowFocusEvent : public EventBase<WindowFocusEvent>
{
public:
    bool gained;
    WindowID win_id;
};

class WindowCloseRequestedEvent : public EventBase<WindowCloseRequestedEvent>
{
public:
    WindowID win_id;
};

}

#endif
