#ifndef YIALITE_WINDOW_H
#define YIALITE_WINDOW_H

#include "../core/core.h"
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
    Window(const WindowConfig& config);
    ~Window();
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    Window(Window&&) = delete;
    Window& operator=(Window&&) = delete;

    //tools
    void showOpenFileDialog(DialogFileCallback callback, void* userdata, const DialogFileFilter* filters, int nfilters, const char* default_location = nullptr, bool allow_many = false);
    WindowConfig getConfig() const { return m_config; }
    void setWidth(int width);
    void setHeight(int height);

    //For internal use only
    void* getNativeHandle();
    const void* getNativeHandle() const;
private:
    struct Impl;
    Impl* m_impl = nullptr;
    WindowConfig m_config;
};

}

#endif