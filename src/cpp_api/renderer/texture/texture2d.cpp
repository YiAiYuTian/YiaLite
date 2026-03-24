#include "texture2d.h"
#include "../../core/yialite_exception.h"
#include "../../renderer/renderer2d.h"

#include "../../thirdparty/stb_image/stb_image.h"
#include <SDL3/SDL.h>

namespace yialite
{

struct Texture2D::Impl
{
    int width, height;

    SDL_Texture* texture = nullptr;
};

Texture2D::Texture2D(std::string_view path, Renderer2D* renderer)
{
    m_impl = new Texture2D::Impl();

    uint8_t* data = stbi_load(path.data(), &m_impl->width, &m_impl->height, nullptr, 4);
    if(!data)
    {
        throw YiaLite_Exception("Failed to load texture: " + std::string(path));
    }

    SDL_Surface* surface = SDL_CreateSurfaceFrom(m_impl->width, m_impl->height, SDL_PIXELFORMAT_RGBA32, data, m_impl->width * 4);
    if(!surface)
    {
        stbi_image_free(data);
        throw YiaLite_Exception("Failed to load texture: " + std::string(SDL_GetError()));
    }

    if(m_impl->texture = SDL_CreateTextureFromSurface(reinterpret_cast<SDL_Renderer*>(renderer->getNativeHandle()), surface); !m_impl->texture)
    {
        SDL_DestroySurface(surface);
        stbi_image_free(data);
        throw YiaLite_Exception("Failed to load texture: " + std::string(SDL_GetError()));
    }

    SDL_DestroySurface(surface);
    stbi_image_free(data);
}

Texture2D::~Texture2D()
{
    SDL_DestroyTexture(m_impl->texture);
    delete m_impl;
}

int Texture2D::getWidth() const
{
    return m_impl->width;
}

int Texture2D::getHeight() const
{
    return m_impl->height;
}

void *Texture2D::getNativeHandle()
{
    return reinterpret_cast<void*>(m_impl->texture);
}

const void *Texture2D::getNativeHandle() const
{
    return reinterpret_cast<const void*>(m_impl->texture);
}

}