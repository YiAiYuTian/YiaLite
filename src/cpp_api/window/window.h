#ifndef YIALITE_WINDOW_H
#define YIALITE_WINDOW_H

#include "../core/core.h"

#include <string>
#include <memory>

namespace yialite
{

typedef uint64_t WindowFlags;

enum WindowFlags_ : uint64_t
{
    WindowFlags_None                = 0,
    WindowFlags_Fullscreen          = 1ULL << 0,
    WindowFlags_Borderless          = 1ULL << 1,
    WindowFlags_Resizable           = 1ULL << 2,
    WindowFlags_MouseGrabbed        = 1ULL << 3,
    WindowFlags_MouseCapture        = 1ULL << 4,
    WindowFlags_KeyboardGrabbed     = 1ULL << 5
};

struct WindowConfig
{
    std::string title = "YiaLite Window";
    int width = 1280;
    int height = 720;
    WindowFlags flags = WindowFlags_None;
};

class YIALITE_API Window
{
    friend class Renderer;
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