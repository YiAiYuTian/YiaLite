#ifndef YIALITE_WINDOW_H
#define YIALITE_WINDOW_H

#include "../core/core.h"
#include "../core/config.h"

namespace yialite
{

class YIALITE_API Window
{
    friend class Renderer2D;
    friend class DevUI;
public:
    Window(const WindowConfig& config);
    ~Window();
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    Window(Window&&) = delete;
    Window& operator=(Window&&) = delete;

    WindowConfig getConfig() const { return m_config; }
    void setWidth(int width);
    void setHeight(int height);
private:
    struct Impl;
    Impl* m_impl = nullptr;
    WindowConfig m_config;
};

}

#endif