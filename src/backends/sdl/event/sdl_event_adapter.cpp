#include "pch.h"
#include "sdl_event_adapter.h"
#include "../../../event/event_abstract.h"
#include "../../../event/event_bus.h"

#include <imgui_impl_sdl3.h>
#include <SDL3/SDL_events.h>

namespace yialite
{

void SDLEventAdapter::poll_event(EventBus& bus, bool has_devui)
{
    while (SDL_PollEvent(&m_event))
    {
        if (has_devui)
            ImGui_ImplSDL3_ProcessEvent(&m_event);

        switch (m_event.type)
        {
        case SDL_EVENT_QUIT:
        {
            QuitEvent e;
            bus.publish(e);
            break;
        }
        case SDL_EVENT_KEY_DOWN:
        case SDL_EVENT_KEY_UP:
        {
            KeyEvent e;
            e.key    = static_cast<Keycode>(m_event.key.key);
            e.repeat = m_event.key.repeat;
            e.down   = m_event.key.down;
            e.mod    = static_cast<Keymod>(m_event.key.mod);
            e.win_id = m_event.key.windowID;
            bus.publish(e);
            break;
        }
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
        case SDL_EVENT_MOUSE_BUTTON_UP:
        {
            MouseButtonEvent e;
            e.btn    = static_cast<MouseButton>(m_event.button.button);
            e.x      = m_event.button.x;
            e.y      = m_event.button.y;
            e.down   = m_event.button.down;
            e.clicks = m_event.button.clicks;
            e.win_id = m_event.button.windowID;
            bus.publish(e);
            break;
        }
        case SDL_EVENT_MOUSE_WHEEL:
        {
            MouseWheelEvent e;
            e.x       = m_event.wheel.x;
            e.y       = m_event.wheel.y;
            e.mouse_x = m_event.wheel.mouse_x;
            e.mouse_y = m_event.wheel.mouse_y;
            e.win_id  = m_event.wheel.windowID;
            bus.publish(e);
            break;
        }
        case SDL_EVENT_MOUSE_MOTION:
        {
            MouseMotionEvent e;
            e.x         = m_event.motion.x;
            e.y         = m_event.motion.y;
            e.rel_x     = m_event.motion.xrel;
            e.rel_y     = m_event.motion.yrel;
            e.btn_flags = m_event.motion.state;
            e.win_id    = m_event.motion.windowID;
            bus.publish(e);
            break;
        }
        case SDL_EVENT_WINDOW_RESIZED:
        {
            WindowResizeEvent e;
            e.w      = m_event.window.data1;
            e.h      = m_event.window.data2;
            e.win_id = m_event.window.windowID;
            bus.publish(e);
            break;
        }
        case SDL_EVENT_WINDOW_MOVED:
        {
            WindowMovedEvent e;
            e.x      = m_event.window.data1;
            e.y      = m_event.window.data2;
            e.win_id = m_event.window.windowID;
            bus.publish(e);
            break;
        }
        case SDL_EVENT_WINDOW_FOCUS_GAINED:
        case SDL_EVENT_WINDOW_FOCUS_LOST:
        {
            WindowFocusEvent e;
            e.gained = (m_event.type == SDL_EVENT_WINDOW_FOCUS_GAINED);
            e.win_id = m_event.window.windowID;
            bus.publish(e);
            break;
        }
        default:
            break;
        }
    }
}

} // namespace yialite
