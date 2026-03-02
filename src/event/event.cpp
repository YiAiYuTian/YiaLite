#include "event.h"

#include <SDL3/SDL.h>

namespace lite
{

struct Event::Impl
{
    SDL_Event event;
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
    while (SDL_PollEvent(&m_impl->event))
    {
        switch (m_impl->event.type)
        {
        case SDL_EVENT_QUIT:
            is_running = false;
            break;
        default:
            break;
        }
    }
}

}