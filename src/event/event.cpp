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

}