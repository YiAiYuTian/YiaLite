#ifndef YIALITE_CONFIG_H
#define YIALITE_CONFIG_H

#include "../utils/base_types.h"

namespace yialite
{

typedef Uint64 WindowFlags;
enum WindowFlags_ : Uint64
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
    const char* title = "YiaLite Window";
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