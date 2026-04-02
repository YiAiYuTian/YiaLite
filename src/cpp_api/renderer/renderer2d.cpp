#include "renderer2d.h"
#include "../core/yialite_exception.h"
#include "../window/window.h"
#include "../renderer/texture/texture2d.h"

#include <SDL3/SDL.h>

namespace yialite
{

struct Renderer2D::Impl
{
    SDL_Renderer* renderer = nullptr;
};

Renderer2D::Renderer2D(Window* window)
{
    m_impl = new Renderer2D::Impl();

    m_impl->renderer = SDL_CreateRenderer(reinterpret_cast<SDL_Window*>(window->getNativeHandle()), nullptr);
    if(!m_impl->renderer)
    {
        delete m_impl;
        throw YiaLite_Exception("Failed to initialize renderer: " + std::string(SDL_GetError()));
    }
    SDL_SetRenderDrawBlendMode(m_impl->renderer, SDL_BLENDMODE_BLEND);
}

Renderer2D::~Renderer2D()
{
    if(m_impl) SDL_DestroyRenderer(m_impl->renderer);
    delete m_impl;
}

void Renderer2D::beginDraw(const Color& background_color)
{
    SDL_SetRenderDrawColor(m_impl->renderer, background_color.r, background_color.g, background_color.b, background_color.a);
    SDL_RenderClear(m_impl->renderer);
}

void Renderer2D::beginDrawF(const FColor& background_color)
{
    SDL_SetRenderDrawColorFloat(m_impl->renderer, background_color.r, background_color.g, background_color.b, background_color.a);
    SDL_RenderClear(m_impl->renderer);
}

void Renderer2D::renderClear(const Color &background_color)
{
    SDL_SetRenderDrawColor(m_impl->renderer, background_color.r, background_color.g, background_color.b, background_color.a);
    SDL_RenderClear(m_impl->renderer);
}

void Renderer2D::renderClearF(const FColor &background_color)
{
    SDL_SetRenderDrawColorFloat(m_impl->renderer, background_color.r, background_color.g, background_color.b, background_color.a);
    SDL_RenderClear(m_impl->renderer);
}

void Renderer2D::endDraw()
{
    SDL_RenderPresent(m_impl->renderer);
}

void Renderer2D::drawPoint(const Vector2f &pos, const Color& color)
{
    SDL_SetRenderDrawColor(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderPoint(m_impl->renderer, pos.x, pos.y);
}

void Renderer2D::drawPoints(const Vector2f* pos, int count, const Color& color)
{
    SDL_SetRenderDrawColor(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderPoints(m_impl->renderer, reinterpret_cast<const SDL_FPoint*>(pos), count);
}

void Renderer2D::drawLine(const Vector2f &start, const Vector2f &end, const Color& color)
{
    SDL_SetRenderDrawColor(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderLine(m_impl->renderer, start.x, start.y, end.x, end.y);
}

void Renderer2D::drawRect(const Vector2f &pos, const Vector2f &size, const Color& color)
{
    SDL_SetRenderDrawColor(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_FRect rect = { pos.x, pos.y, size.x, size.y};
    SDL_RenderRect(m_impl->renderer, &rect);
}

void Renderer2D::drawRect(const FRect &rect, const Color& color)
{
    SDL_SetRenderDrawColor(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderRect(m_impl->renderer, reinterpret_cast<const SDL_FRect*>(&rect));
}

void Renderer2D::drawFillRect(const Vector2f &pos, const Vector2f &size, const Color& color)
{
    SDL_FRect rect = { pos.x, pos.y, size.x, size.y};
    SDL_RenderFillRect(m_impl->renderer, &rect);
}

void Renderer2D::drawFillRect(const FRect &rect, const Color& color)
{
    SDL_RenderFillRect(m_impl->renderer, reinterpret_cast<const SDL_FRect*>(&rect));
}

void Renderer2D::drawTexture(Texture2D &texture, const FRect* src_rect, const FRect &dst_rect, uint8_t alpha)
{
    SDL_Texture* sdl_texture = reinterpret_cast<SDL_Texture*>(texture.getNativeHandle());
    
    SDL_SetTextureAlphaMod(sdl_texture, alpha);
    SDL_RenderTexture(
        m_impl->renderer,
        sdl_texture,
        reinterpret_cast<const SDL_FRect*>(src_rect),
        reinterpret_cast<const SDL_FRect*>(&dst_rect)
    );
}

void Renderer2D::drawPointF(const Vector2f &pos, const FColor& color)
{
    SDL_SetRenderDrawColorFloat(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderPoint(m_impl->renderer, pos.x, pos.y);
}

void Renderer2D::drawPointsF(const Vector2f *pos, int count, const FColor& color)
{
    SDL_SetRenderDrawColorFloat(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderPoints(m_impl->renderer, reinterpret_cast<const SDL_FPoint*>(pos), count);
}

void Renderer2D::drawLineF(const Vector2f &start, const Vector2f &end, const FColor& color)
{
    SDL_SetRenderDrawColorFloat(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderLine(m_impl->renderer, start.x, start.y, end.x, end.y);
}

void Renderer2D::drawRectF(const Vector2f &pos, const Vector2f &size, const FColor& color)
{
    SDL_SetRenderDrawColorFloat(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_FRect rect = { pos.x, pos.y, size.x, size.y};
    SDL_RenderRect(m_impl->renderer, &rect);
}

void Renderer2D::drawRectF(const FRect &rect, const FColor& color)
{
    SDL_SetRenderDrawColorFloat(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderRect(m_impl->renderer, reinterpret_cast<const SDL_FRect*>(&rect));
}

void Renderer2D::drawFillRectF(const Vector2f &pos, const Vector2f &size, const FColor& color)
{
    SDL_SetRenderDrawColorFloat(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_FRect rect = { pos.x, pos.y, size.x, size.y};
    SDL_RenderFillRect(m_impl->renderer, &rect);
}

void Renderer2D::drawFillRectF(const FRect &rect, const FColor& color)
{
    SDL_SetRenderDrawColorFloat(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(m_impl->renderer, reinterpret_cast<const SDL_FRect*>(&rect));
}

void Renderer2D::drawTextureF(Texture2D& texture, const FRect* src_rect, const FRect& dst_rect, float alpha)
{
    SDL_Texture* sdl_texture = reinterpret_cast<SDL_Texture*>(texture.getNativeHandle());
    
    SDL_SetTextureAlphaModFloat(sdl_texture, alpha);
    SDL_RenderTexture(
        m_impl->renderer,
        sdl_texture,
        reinterpret_cast<const SDL_FRect*>(src_rect),
        reinterpret_cast<const SDL_FRect*>(&dst_rect)
    );
}

void Renderer2D::setRenderScale(const Vector2f &size)
{
    SDL_SetRenderScale(m_impl->renderer, size.x, size.y);
}

void Renderer2D::setRenderTarget(Texture2D* texture)
{
    SDL_SetRenderTarget(m_impl->renderer, texture ? reinterpret_cast<SDL_Texture*>(texture->getNativeHandle()) : nullptr);
}

void *Renderer2D::getNativeHandle()
{
    return reinterpret_cast<void*>(m_impl->renderer);
}

const void *Renderer2D::getNativeHandle() const
{
    return reinterpret_cast<const void*>(m_impl->renderer);
}

}