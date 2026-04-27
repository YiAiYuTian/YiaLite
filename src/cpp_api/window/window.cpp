#include "window.h"
#include "../core/yialite_exception.h"
#include "../core/logger.h"

#include <SDL3/SDL.h>

namespace yialite
{

static SDL_WindowFlags convertToSDLWindowFlags(const WindowFlags flags)
{
    constexpr static std::pair<WindowFlags, SDL_WindowFlags> flag_map[] = {
        {WindowFlags_Fullscreen,      SDL_WINDOW_FULLSCREEN},
        {WindowFlags_Borderless,      SDL_WINDOW_BORDERLESS},
        {WindowFlags_Resizable,       SDL_WINDOW_RESIZABLE},
        {WindowFlags_MouseGrabbed,    SDL_WINDOW_MOUSE_GRABBED},
        {WindowFlags_MouseCapture,    SDL_WINDOW_MOUSE_CAPTURE},
        {WindowFlags_KeyboardGrabbed, SDL_WINDOW_KEYBOARD_GRABBED}
    };

    SDL_WindowFlags sdl_flags = 0;
    for (const auto& [lite_flag, sdl_flag] : flag_map)
    {
        if (flags & lite_flag)
            sdl_flags |= sdl_flag;
    }

    return sdl_flags;
}

struct Window::Impl
{
    SDL_Window* window = nullptr;
};

Window::Window(const WindowConfig& config)
{
    m_config = config;
    m_impl = new Window::Impl();

    m_impl->window = SDL_CreateWindow(config.title, config.width, config.height, convertToSDLWindowFlags(config.flags));
    if(!m_impl->window)
    {
        delete m_impl;
        throw YiaLite_Exception("Failed to initialize window: " + std::string(SDL_GetError()));
    }

    Logger::info("Window initialized successfully: {}({}, {})", config.title, config.width, config.height);
}

Window::~Window()
{
    if(m_impl) SDL_DestroyWindow(m_impl->window);
    delete m_impl;
}

void Window::showOpenFileDialog(DialogFileCallback callback, void* userdata, const DialogFileFilter* filters, int nfilters, const char* default_location, bool allow_many)
{
    SDL_ShowOpenFileDialog(callback, 
        userdata, 
        m_impl->window, 
        reinterpret_cast<const SDL_DialogFileFilter*>(filters),
        nfilters,
        default_location,
        allow_many
    );
}

void Window::setWidth(int width)
{
    m_config.width = width;
    SDL_SetWindowSize(m_impl->window, width, m_config.height);
}

void Window::setHeight(int height)
{
    m_config.height = height;
    SDL_SetWindowSize(m_impl->window, m_config.width, height);
}

void *Window::getNativeHandle()
{
    return reinterpret_cast<void*>(m_impl->window);
}

const void *Window::getNativeHandle() const
{
    return reinterpret_cast<const void*>(m_impl->window);
}

}