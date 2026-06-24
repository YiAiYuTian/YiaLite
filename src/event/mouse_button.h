#ifndef YIALITE_MOUSE_BUTTON_H
#define YIALITE_MOUSE_BUTTON_H

#include "../utils/base_types.h"
#include "../core/flag_macros.h"

namespace yialite
{

//Copy in SDL_mouse.h

//mouse button
enum class MouseButton : Uint8
{
    LEFT   = 1,
    MIDDLE = 2,
    RIGHT  = 3,
    X1     = 4,
    X2     = 5
};

//mouse button flags
#define YIALITE_MOUSE_BUTTON_MASK(x)  (1u << ((static_cast<Uint8>(x))-1))
typedef Uint32 MouseButtonFlags_;
enum class MouseButtonFlags : Uint32
{
    LMASK =  YIALITE_MOUSE_BUTTON_MASK(MouseButton::LEFT),
    MMASK =  YIALITE_MOUSE_BUTTON_MASK(MouseButton::MIDDLE),
    RMASK =  YIALITE_MOUSE_BUTTON_MASK(MouseButton::RIGHT),
    X1MASK = YIALITE_MOUSE_BUTTON_MASK(MouseButton::X1),
    X2MASK = YIALITE_MOUSE_BUTTON_MASK(MouseButton::X2)
};

namespace detail
{
    inline constexpr MouseButtonFlags_ to_mouse_btn_flags_(MouseButtonFlags v)
    {
        return static_cast<MouseButtonFlags_>(v);
    }
}

GEN_FLAG_BIN_OP_AND_ASSIGN_OP(|, MouseButtonFlags, MouseButtonFlags_, detail::to_mouse_btn_flags_)
GEN_FLAG_BIN_OP_AND_ASSIGN_OP(&, MouseButtonFlags, MouseButtonFlags_, detail::to_mouse_btn_flags_)

}

#endif