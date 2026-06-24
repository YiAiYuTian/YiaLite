#ifndef YIALITE_WINDOW_MANAGER_H
#define YIALITE_WINDOW_MANAGER_H

#include "window.h"
#include "../core/core.h"
#include "../utils/containers/yia_hashmap.h"

namespace yialite
{

class YIALITE_API WindowManager
{
public:
    ~WindowManager();

    static Result<WindowManager*> create(const WindowConfig& config);
    static void destroy(WindowManager* mgr);

    WindowID create_window(const WindowConfig& config);
    void destroy_window(WindowID id);

    IWindow* get_window(WindowID id);
    inline IWindow* get_first_window() { return get_window(m_first_window_id); }

    //For internal use only
    void* get_native_handle(WindowID id);
    const void* get_native_handle(WindowID id) const;
private:
    WindowManager() = default;
private:
    HashMap<WindowID, IWindow*> m_windows;
    WindowID m_first_window_id = INVALID_WINDOW_ID;
};

}

#endif