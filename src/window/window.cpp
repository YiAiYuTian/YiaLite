#include "pch.h"
#include "window.h"
#include "../utils/memory/allocator.h"
#include "../backends/sdl/window/sdl_window.h"

namespace yialite
{

Result<IWindow*> IWindow::create(const WindowConfig& config)
{
    return SDLWindow::create(config);
}

void IWindow::destroy(IWindow* window)
{
    SDLWindow::destroy(window);
}

}