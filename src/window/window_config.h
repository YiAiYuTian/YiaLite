#ifndef YIALITE_WINDOW_CONFIG_H
#define YIALITE_WINDOW_CONFIG_H

#include "../utils/handle.h"
#include "../utils/base_types.h"
#include "../core/flag_macros.h"

namespace yialite
{

struct WindowTag;
using WindowID = Handle<Uint32, WindowTag>; 
inline constexpr WindowID INVALID_WINDOW_ID = WindowID{0};

typedef Uint64 WindowFlags_;
enum class WindowFlags : Uint64
{
    None                = 0,
    Fullscreen          = 1U << 0,
    Borderless          = 1U << 1,
    Resizable           = 1U << 2,
    MouseGrabbed        = 1U << 3,
    MouseCapture        = 1U << 4,
    KeyboardGrabbed     = 1U << 5
};

namespace detail
{
    inline constexpr WindowFlags_ to_window_flags_(WindowFlags v)
    {
        return static_cast<WindowFlags_>(v);
    }
}

GEN_FLAG_BIN_OP_AND_ASSIGN_OP(|, WindowFlags, WindowFlags_, detail::to_window_flags_)
GEN_FLAG_BIN_OP_AND_ASSIGN_OP(&, WindowFlags, WindowFlags_, detail::to_window_flags_)

struct WindowConfig
{
    const char* title = "YiaLite Window";
    int width = 1280;
    int height = 720;
    WindowFlags_ flags = 0;
};

}

#endif