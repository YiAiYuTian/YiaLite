#include "renderer.h"
#include "../core/yialite_exception.h"
#include "../window/window.h"

#include <SDL3/SDL.h>

namespace yialite
{

struct Renderer::Impl
{
    SDL_Renderer* renderer = nullptr;
};

Renderer::Renderer(Window* window)
{
    m_impl = new Renderer::Impl();

    m_impl->renderer = SDL_CreateRenderer(window->getSDLWindow(), nullptr);
    if(!m_impl->renderer) throw YiaLite_Exception("Failed to initialize renderer: " + std::string(SDL_GetError()));
    SDL_SetRenderDrawBlendMode(m_impl->renderer, SDL_BLENDMODE_BLEND);
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_impl->renderer);
    delete m_impl;
}

void Renderer::beginDraw(Color background_color)
{
    SDL_SetRenderDrawColor(m_impl->renderer, background_color.r, background_color.g, background_color.b, background_color.a);
    SDL_RenderClear(m_impl->renderer);
}

void Renderer::endDraw()
{
    SDL_RenderPresent(m_impl->renderer);
}

void Renderer::drawPoint(const Vector2f &pos, Color color)
{
    SDL_SetRenderDrawColor(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderPoint(m_impl->renderer, pos.x, pos.y);
}

void Renderer::drawPoints(const Vector2f* pos, int count, Color color)
{
    SDL_SetRenderDrawColor(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderPoints(m_impl->renderer, reinterpret_cast<const SDL_FPoint*>(pos), count);
}

void Renderer::drawLine(const Vector2f &start, const Vector2f &end, Color color)
{
    SDL_SetRenderDrawColor(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderLine(m_impl->renderer, start.x, start.y, end.x, end.y);
}

void Renderer::drawRect(const Vector2f &pos, const Vector2f &size, Color color)
{
    SDL_FRect frect = { pos.x, pos.y, size.x, size.y };
    SDL_SetRenderDrawColor(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderRect(m_impl->renderer, &frect);
}

void Renderer::drawRect(const FRect &rect, Color color)
{
    SDL_FRect frect = { rect.x, rect.y, rect.w, rect.h };
    SDL_SetRenderDrawColor(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderRect(m_impl->renderer, &frect);
}

void Renderer::drawFillRect(const Vector2f &pos, const Vector2f &size, Color color)
{
    SDL_FRect frect = { pos.x, pos.y, size.x, size.y };
    SDL_SetRenderDrawColor(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(m_impl->renderer, &frect);
}

void Renderer::drawFillRect(const FRect &rect, Color color)
{
    SDL_FRect frect = { rect.x, rect.y, rect.w, rect.h };
    SDL_SetRenderDrawColor(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(m_impl->renderer, &frect);
}

void Renderer::fdrawPoint(const Vector2f &pos, FColor color)
{
    SDL_SetRenderDrawColorFloat(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderPoint(m_impl->renderer, pos.x, pos.y);
}

void Renderer::fdrawPoints(const Vector2f *pos, int count, FColor color)
{
    SDL_SetRenderDrawColorFloat(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderPoints(m_impl->renderer, reinterpret_cast<const SDL_FPoint*>(pos), count);
}

void Renderer::fdrawLine(const Vector2f &start, const Vector2f &end, FColor color)
{
    SDL_SetRenderDrawColorFloat(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderLine(m_impl->renderer, start.x, start.y, end.x, end.y);
}

void Renderer::fdrawRect(const Vector2f &pos, const Vector2f &size, FColor color)
{
    SDL_FRect frect = { pos.x, pos.y, size.x, size.y };
    SDL_SetRenderDrawColorFloat(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderRect(m_impl->renderer, &frect);
}

void Renderer::fdrawRect(const FRect &rect, FColor color)
{
    SDL_FRect frect = { rect.x, rect.y, rect.w, rect.h };
    SDL_SetRenderDrawColorFloat(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderRect(m_impl->renderer, &frect);
}

void Renderer::fdrawFillRect(const Vector2f &pos, const Vector2f &size, FColor color)
{
    SDL_FRect frect = { pos.x, pos.y, size.x, size.y };
    SDL_SetRenderDrawColorFloat(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(m_impl->renderer, &frect);
}

void Renderer::fdrawFillRect(const FRect &rect, FColor color)
{
    SDL_FRect frect = { rect.x, rect.y, rect.w, rect.h };
    SDL_SetRenderDrawColorFloat(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(m_impl->renderer, &frect);
}

}