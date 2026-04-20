#ifndef YIALITE_CONFIG_H
#define YIALITE_CONFIG_H

#include <string>

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

struct ContextConfig
{
    WindowConfig window_config;
    bool enable_devui = false;
};

}

#endif