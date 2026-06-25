#include "pch.h"
#include "window_manager.h"
#include "../utils/memory/allocator.h"
#include "../core/logger.h"
#include "../backends/sdl/window/sdl_window.h"

namespace yialite
{

WindowManager::~WindowManager()
{
    for(auto& pair : m_windows)
    {
        pair.second->destroy();
        DEALLOCATE_OBJECT(IWindow, pair.second);
    }
    m_windows.clear();
}

Result<WindowManager*> WindowManager::create(const WindowConfig& config)
{
    WindowManager* wm = ALLOCATE_OBJECT(WindowManager);
    if(!wm) return Result<WindowManager*>(ErrorCode::OutOfMemory);
    
    wm->m_first_window_id = wm->create_window(config);
    return wm;
}

void WindowManager::destroy(WindowManager *wm)
{
    DEALLOCATE_OBJECT(WindowManager, wm);
}

WindowID WindowManager::create_window(const WindowConfig &config)
{
    IWindow* win = ALLOCATE_OBJECT(SDLWindow);
    if(!win) return INVALID_WINDOW_ID;

    auto win_init_result = win->init(config);
    if(!win_init_result)
    {
        Logger::error("Failed to initialize window: {}", win_init_result.error().message());
        return INVALID_WINDOW_ID;
    }

    WindowID id = win->get_id();
    m_windows.insert(id, win);
    return id;
}

void WindowManager::destroy_window(WindowID id)
{
    auto window = m_windows.find(id);
    if(!window) return;

    (*window)->destroy();
    DEALLOCATE_OBJECT(IWindow, *window);
    m_windows.remove(id);
}

IWindow *WindowManager::get_window(WindowID id)
{
    auto window = m_windows.find(id);
    if(!window) return nullptr;

    return *window;
}

void* WindowManager::get_native_handle(WindowID id)
{
    auto window = m_windows.find(id);
    if(!window) return nullptr;

    return (*window)->get_native_handle();
}

const void *WindowManager::get_native_handle(WindowID id) const
{
    auto window = m_windows.find(id);
    if(!window) return nullptr;

    return (*window)->get_native_handle();
}

}