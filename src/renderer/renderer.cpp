#include "renderer.h"
#include "../core/lite_exception.h"
#include "../window/window.h"

#include <SDL3/SDL.h>

namespace lite
{

struct Renderer::Impl
{
    SDL_Renderer* renderer = nullptr;
};

Renderer::Renderer(Window* window)
{
    m_impl = new Renderer::Impl();

    m_impl->renderer = SDL_CreateRenderer(window->getSDLWindow(), nullptr);
    if(!m_impl->renderer) throw Lite_Exception("Failed to initialize renderer: " + std::string(SDL_GetError()));
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_impl->renderer);
    delete m_impl;
}

}