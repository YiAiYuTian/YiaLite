#include "event.h"
#include "../utils/memory/allocator.h"

#include <imgui_impl_sdl3.h>
#include <SDL3/SDL.h>

namespace yialite
{

struct Event::Impl
{
    SDL_Event event;

    bool has_devui = false;

    QuitEventCallback quit_event_callback = nullptr;
    KeyEventCallback key_event_callback = nullptr;
    MouseButtonEventCallback mouse_event_callback = nullptr;
    MouseWheelEventCallback mouse_wheel_event_callback = nullptr;
    MouseMotionEventCallback mouse_motion_event_callback = nullptr;
    WindowResizedEventCallback window_resized_event_callback = nullptr;
    WindowMovedEventCallback window_moved_event_callback = nullptr;
    WindowFocusGainedEventCallback window_focus_gained_event_callback = nullptr;
    WindowFocusLostEventCallback window_focus_lost_event_callback = nullptr;
};

Result<Event*> Event::create()
{
    Event* e = ALLOCATE_OBJECT(Event);
    e->m_impl = ALLOCATE_OBJECT(Event::Impl);
    return e;
}

Event::~Event()
{
    DEALLOCATE_OBJECT(Event::Impl, m_impl);
    m_impl = nullptr;
}

void Event::destroy(Event* event)
{
    DEALLOCATE_OBJECT(Event, event);
}

void Event::on_update()
{
    auto& sdl_event = m_impl->event;
    while (SDL_PollEvent(&sdl_event))
    {
        if(m_impl->has_devui)
            ImGui_ImplSDL3_ProcessEvent(&sdl_event);

        switch (sdl_event.type)
        {
        case SDL_EVENT_QUIT:
            if(m_impl->quit_event_callback)
                m_impl->quit_event_callback();
            break;
        case SDL_EVENT_KEY_DOWN:
            if(m_impl->key_event_callback)
            {
                m_impl->key_event_callback(
                    sdl_event.key.key,
                    sdl_event.key.repeat,
                    sdl_event.key.down,
                    sdl_event.key.mod
                );
            }
            break;
        case SDL_EVENT_KEY_UP:
            if(m_impl->key_event_callback)
            {
                m_impl->key_event_callback(
                    sdl_event.key.key,
                    sdl_event.key.repeat,
                    sdl_event.key.down,
                    sdl_event.key.mod
                );
            }
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if(m_impl->mouse_event_callback)
            {
                m_impl->mouse_event_callback(
                    sdl_event.button.button,
                    sdl_event.button.x,
                    sdl_event.button.y,
                    sdl_event.button.down,
                    sdl_event.button.clicks
                );
            }
            break;
        case SDL_EVENT_MOUSE_BUTTON_UP:
            if(m_impl->mouse_event_callback)
            {
                m_impl->mouse_event_callback(
                    sdl_event.button.button,
                    sdl_event.button.x,
                    sdl_event.button.y,
                    sdl_event.button.down,
                    sdl_event.button.clicks
                );
            }
            break;
        case SDL_EVENT_MOUSE_WHEEL:
            if(m_impl->mouse_wheel_event_callback)
            {
                m_impl->mouse_wheel_event_callback(
                    sdl_event.wheel.x,
                    sdl_event.wheel.y,
                    sdl_event.wheel.mouse_x,
                    sdl_event.wheel.mouse_y
                );
            }
            break;
        case SDL_EVENT_MOUSE_MOTION:
            if(m_impl->mouse_motion_event_callback)
            {
                m_impl->mouse_motion_event_callback(
                    sdl_event.motion.x,
                    sdl_event.motion.y,
                    sdl_event.motion.xrel,
                    sdl_event.motion.yrel,
                    sdl_event.motion.state
                );
            }
            break;
        case SDL_EVENT_WINDOW_RESIZED:
            if(m_impl->window_resized_event_callback)
            {
                m_impl->window_resized_event_callback(
                    sdl_event.window.data1,
                    sdl_event.window.data2
                );
            }
            break;
        case SDL_EVENT_WINDOW_MOVED:
            if(m_impl->window_moved_event_callback)
            {
                m_impl->window_moved_event_callback(
                    sdl_event.window.data1,
                    sdl_event.window.data2
                );
            }
            break;
        case SDL_EVENT_WINDOW_FOCUS_GAINED:
            if(m_impl->window_focus_gained_event_callback)
            {
                m_impl->window_focus_gained_event_callback();
            }
            break;
        case SDL_EVENT_WINDOW_FOCUS_LOST:
            if(m_impl->window_focus_lost_event_callback)
            {
                m_impl->window_focus_lost_event_callback();
            }
            break;
        default:
            break;
        }
    }
}

void Event::register_devui_event(DevUI* devui)
{
    m_impl->has_devui = (devui != nullptr);
}

void Event::register_quit_event_callback(QuitEventCallback&& callback)
{
    m_impl->quit_event_callback = yialite::move(callback);
}

void Event::register_key_event_callback(KeyEventCallback&& callback)
{
    m_impl->key_event_callback = yialite::move(callback);
}

void Event::register_mouse_button_event_callback(MouseButtonEventCallback&& callback)
{
    m_impl->mouse_event_callback = yialite::move(callback);
}

void Event::register_mouse_wheel_event_callback(MouseWheelEventCallback&& callback)
{
    m_impl->mouse_wheel_event_callback = yialite::move(callback);
}

void Event::register_mouse_motion_event_callback(MouseMotionEventCallback&& callback)
{
    m_impl->mouse_motion_event_callback = yialite::move(callback);
}

void Event::register_window_resized_event_callback(WindowResizedEventCallback&& callback)
{
    m_impl->window_resized_event_callback = yialite::move(callback);
}

void Event::register_window_moved_event_callback(WindowMovedEventCallback&& callback)
{
    m_impl->window_moved_event_callback = yialite::move(callback);
}

void Event::register_window_focus_gained_event_callback(WindowFocusGainedEventCallback&& callback)
{
    m_impl->window_focus_gained_event_callback = yialite::move(callback);
}

void Event::register_window_focus_lost_event_callback(WindowFocusLostEventCallback&& callback)
{
    m_impl->window_focus_lost_event_callback = yialite::move(callback);
}

}
