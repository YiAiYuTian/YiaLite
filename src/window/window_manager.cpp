#include "pch.h"
#include "window_manager.h"
#include "../utils/memory/allocator.h"

namespace yialite
{

WindowManager::~WindowManager()
{
    for(auto pair : m_windows)
    {
        IWindow::destroy(pair.second);
    }
    m_windows.clear();
}

Result<WindowManager*> WindowManager::create(const WindowConfig& config)
{
    WindowManager* mgr = ALLOCATE_OBJECT(WindowManager);
    if(!mgr) return Result<WindowManager*>(ErrorCode::OutOfMemory);
    
    mgr->m_first_window_id = mgr->create_window(config);
    return mgr;
}

void WindowManager::destroy(WindowManager *mgr)
{
    DEALLOCATE_OBJECT(WindowManager, mgr);
}

WindowID WindowManager::create_window(const WindowConfig &config)
{
    auto window_result = IWindow::create(config);
    if(!window_result) return INVALID_WINDOW_ID;

    auto& window = window_result.value();
    WindowID id = window->get_id();
    m_windows.insert(id, window);
    return id;
}

void WindowManager::destroy_window(WindowID id)
{
    auto window = m_windows.find(id);
    if(!window) return;

    IWindow::destroy(*window);
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