#include "event.h"

#include <SDL3/SDL.h>

namespace lite
{

struct Event::Impl
{
    SDL_Event event;

    void* data = nullptr;

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

Event::Event()
{
    m_impl = new Event::Impl();
}

Event::~Event()
{
    delete m_impl;
}

void Event::onUpdate()
{
    auto& sdl_event = m_impl->event;
    while (SDL_PollEvent(&sdl_event))
    {
        switch (sdl_event.type)
        {
        case SDL_EVENT_QUIT:
            if(m_impl->quit_event_callback) 
                m_impl->quit_event_callback(m_impl->data);
            break;
        case SDL_EVENT_KEY_DOWN:
            if(m_impl->key_event_callback)
            {
                m_impl->key_event_callback(
                    sdl_event.key.key,
                    sdl_event.key.repeat,
                    sdl_event.key.down,
                    sdl_event.key.mod,
                    m_impl->data
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
                    sdl_event.key.mod,
                    m_impl->data
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
                    sdl_event.button.clicks,
                    m_impl->data
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
                    sdl_event.button.clicks,
                    m_impl->data
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
                    sdl_event.wheel.mouse_y,
                    m_impl->data
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
                    sdl_event.motion.state,
                    m_impl->data
                );
            }
            break;
        case SDL_EVENT_WINDOW_RESIZED:
            if(m_impl->window_resized_event_callback)
            {
                m_impl->window_resized_event_callback(
                    sdl_event.window.data1,
                    sdl_event.window.data2,
                    m_impl->data
                );
            }
            break;
        case SDL_EVENT_WINDOW_MOVED:
            if(m_impl->window_moved_event_callback)
            {
                m_impl->window_moved_event_callback(
                    sdl_event.window.data1,
                    sdl_event.window.data2,
                    m_impl->data
                );
            }
            break;
        case SDL_EVENT_WINDOW_FOCUS_GAINED:
            if(m_impl->window_focus_gained_event_callback)
            {
                m_impl->window_focus_gained_event_callback(
                    m_impl->data
                );
            }
            break;
        case SDL_EVENT_WINDOW_FOCUS_LOST:
            if(m_impl->window_focus_lost_event_callback)
            {
                m_impl->window_focus_lost_event_callback(
                    m_impl->data
                );
            }
            break;
        default:
            break;
        }
    }
}

void Event::setGlobalData(void *data)
{
    m_impl->data = data;
}

void Event::registerQuitEventCallback(QuitEventCallback callback)
{
    m_impl->quit_event_callback = callback;
}

void Event::registerKeyEventCallback(KeyEventCallback callback)
{
    m_impl->key_event_callback = callback;
}

void Event::registerMouseButtonEventCallback(MouseButtonEventCallback callback)
{
    m_impl->mouse_event_callback = callback;
}

void Event::registerMouseWheelEventCallback(MouseWheelEventCallback callback)
{
    m_impl->mouse_wheel_event_callback = callback;
}

void Event::registerMouseMotionEventCallback(MouseMotionEventCallback callback)
{
    m_impl->mouse_motion_event_callback = callback;
}

void Event::registerWindowResizedEventCallback(WindowResizedEventCallback callback)
{
    m_impl->window_resized_event_callback = callback;
}

void Event::registerWindowMovedEventCallback(WindowMovedEventCallback callback)
{
    m_impl->window_moved_event_callback = callback;
}

void Event::registerWindowFocusGainedEventCallback(WindowFocusGainedEventCallback callback)
{
    m_impl->window_focus_gained_event_callback = callback;
}

void Event::registerWindowFocusLostEventCallback(WindowFocusLostEventCallback callback)
{
    m_impl->window_focus_lost_event_callback = callback;
}

}