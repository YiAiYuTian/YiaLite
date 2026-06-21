#ifndef YIALITE_WINDOW_H
#define YIALITE_WINDOW_H

#include "../core/core.h"
#include "../core/result.h"
#include "../core/config.h"

namespace yialite
{

typedef void (*DialogFileCallback)(void *userdata, const char * const *filelist, int filter);

struct DialogFileFilter
{
    const char* name;
    const char* pattern;
};

class YIALITE_API Window
{
public:
    ~Window();
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    Window(Window&& other) noexcept;
    Window& operator=(Window&& other) noexcept;

    static Result<Window*> create(const WindowConfig& config);
    static void destroy(Window* window);

    void show_open_file_dialog(DialogFileCallback callback, void* userdata,
        const DialogFileFilter* filters, int nfilters,
        const char* default_location = nullptr, bool allow_many = false);

    WindowConfig get_config() const { return m_config; }
    void set_width(int width);
    void set_height(int height);

    //For internal use only
    void* get_native_handle();
    const void* get_native_handle() const;

    explicit operator bool() const noexcept { return m_impl != nullptr; }
private:
    Window() = default;
    struct Impl;
    Impl* m_impl = nullptr;
    WindowConfig m_config;
};

}

#endif
