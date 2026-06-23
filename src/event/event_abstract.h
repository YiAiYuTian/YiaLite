#ifndef YIALITE_EVENT_ABSTRACT_H
#define YIALITE_EVENT_ABSTRACT_H

#include "keycode.h"
#include "mouse_button.h"
#include "../utils/delegate.h"
#include "../utils/base_types.h"

#include <tuple>

namespace yialite
{

enum class EventType : Uint32
{
    None = 0,
    Quit,

    Key,
    MouseButton,
    MouseWheel,
    MouseMotion,

    WindowResize,
    WindowMoved,
    WindowFocus,

    Max
};

enum class EventPriority
{
    UI = 0,
    GameLogic = 1,
    Background = 2
};
constexpr size_t EVENT_PRIORITY_COUNT = 3;

class IEvent
{
public:
    virtual ~IEvent() = default;
    virtual EventType get_type() const = 0;
public:
    bool consumed = false;
};

class QuitEvent : public IEvent
{
public:
    EventType get_type() const override { return EventType::Quit; }
};

class KeyEvent : public IEvent
{
public:
    Keycode key;
    bool repeat;
    bool down;
    Keymod mod;

    EventType get_type() const override { return EventType::Key; }
};

class MouseButtonEvent : public IEvent
{
public:
    MouseButton btn;
    float x, y;
    bool down;
    Uint8 clicks;

    EventType get_type() const override { return EventType::MouseButton; }
};

class MouseWheelEvent : public IEvent
{
public:
    float x, y;
    float mouse_x, mouse_y;

    EventType get_type() const override { return EventType::MouseWheel; }
};

class MouseMotionEvent : public IEvent
{
public:
    float x, y;
    float rel_x, rel_y;
    MouseButtonFlags_ btn_flags;

    EventType get_type() const override { return EventType::MouseMotion; }
};

class WindowResizeEvent : public IEvent
{
public:
    int w, h;

    EventType get_type() const override { return EventType::WindowResize; }
};

class WindowMovedEvent : public IEvent
{
public:
    int x, y;

    EventType get_type() const override { return EventType::WindowMoved; }
};

class WindowFocusEvent : public IEvent
{
public:
    bool gained;

    EventType get_type() const override { return EventType::WindowFocus; }
};

template<EventType E, typename EventClass>
struct EventMeta
{
    static constexpr EventType Enum = E;
    using Type = EventClass;
};

using EventMetaMap = std::tuple<
    EventMeta<EventType::Quit, QuitEvent>,
    EventMeta<EventType::Key, KeyEvent>,
    EventMeta<EventType::MouseButton, MouseButtonEvent>,
    EventMeta<EventType::MouseWheel, MouseWheelEvent>,
    EventMeta<EventType::MouseMotion, MouseMotionEvent>,
    EventMeta<EventType::WindowResize, WindowResizeEvent>,
    EventMeta<EventType::WindowMoved, WindowMovedEvent>,
    EventMeta<EventType::WindowFocus, WindowFocusEvent>
>;

namespace detail
{
    template<typename Map, typename T>
    struct event_type_to_enum;

    template<typename T, EventType E, typename EventClass, typename... Rest>
    struct event_type_to_enum<std::tuple<EventMeta<E, EventClass>, Rest...>, T>
        : std::conditional_t<
        std::is_same_v<T, EventClass>,
        std::integral_constant<EventType, E>,
        event_type_to_enum<std::tuple<Rest...>, T>>
    {};

    template<typename T>
    struct event_type_to_enum<std::tuple<>, T>
    {
        static_assert(sizeof(T) == 0, "This event type is not registered in EventMetaMap");
    };

    template<typename Map, EventType TargetE>
    struct event_enum_to_type;

    template<EventType TargetE, EventType E, typename EventClass, typename... Rest>
    struct event_enum_to_type<std::tuple<EventMeta<E, EventClass>, Rest...>, TargetE>
        : std::conditional_t<
        (E == TargetE),
        std::type_identity<EventClass>,
        event_enum_to_type<std::tuple<Rest...>, TargetE>>
    {};

    template<EventType TargetE>
    struct event_enum_to_type<std::tuple<>, TargetE>
    {
        static_assert(TargetE != TargetE, "No matching event struct for this EventType");
    };
}

template<typename T>
constexpr EventType get_event_type_enum()
{
    return detail::event_type_to_enum<EventMetaMap, T>::value;
}

template<EventType TargetE>
using event_from_enum = typename detail::event_enum_to_type<EventMetaMap, TargetE>::type;

}

#endif
