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

Texture2D::Texture2D(const char* path, Renderer2D* renderer)
{
    m_impl = new Texture2D::Impl();

    uint8_t* data = stbi_load(path, &m_impl->width, &m_impl->height, nullptr, 4);
    if(!data)
    {
        delete m_impl;
        throw YiaLite_Exception("Failed to load texture(" + std::string(path) + ")" + ": " + stbi_failure_reason());
    }

    SDL_Surface* surface = SDL_CreateSurfaceFrom(m_impl->width, m_impl->height, SDL_PIXELFORMAT_RGBA32, data, m_impl->width * 4);
    if(!surface)
    {
        stbi_image_free(data);
        delete m_impl;
        throw YiaLite_Exception("Failed to load texture(" + std::string(path) + ")" + ": " + std::string(SDL_GetError()));
    }

    if(m_impl->texture = SDL_CreateTextureFromSurface(reinterpret_cast<SDL_Renderer*>(renderer->getNativeHandle()), surface); !m_impl->texture)
    {
        SDL_DestroySurface(surface);
        stbi_image_free(data);
        delete m_impl;
        throw YiaLite_Exception("Failed to load texture(" + std::string(path) + ")" + ": " + std::string(SDL_GetError()));
    }

    SDL_DestroySurface(surface);
    stbi_image_free(data);
}

Texture2D::Texture2D(int width, int height, Renderer2D *renderer, bool is_target)
{
    m_impl = new Texture2D::Impl();

    if(m_impl->texture = SDL_CreateTexture(
        reinterpret_cast<SDL_Renderer*>(renderer->getNativeHandle()), 
        SDL_PIXELFORMAT_RGBA32, is_target ? SDL_TEXTUREACCESS_TARGET : SDL_TEXTUREACCESS_STATIC, width, height
        ); !m_impl->texture)
    {
        throw YiaLite_Exception("Failed to create texture: " + std::string(SDL_GetError()));
    }

    m_impl->width = width;
    m_impl->height = height;
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