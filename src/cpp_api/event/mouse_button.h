/* 
    Simple DirectMedia Layer
    Copyright (C) 1997-2025 Sam Lantinga <slouken@libsdl.org>
    Modified for YiaLite
*/

#ifndef YIALITE_MOUSE_BUTTON_H
#define YIALITE_MOUSE_BUTTON_H

#include <stdint.h>

namespace yialite
{
    typedef uint8_t MouseButton;
}

#define YIALITE_MOUSE_BUTTON_LEFT     1
#define YIALITE_MOUSE_BUTTON_MIDDLE   2
#define YIALITE_MOUSE_BUTTON_RIGHT    3
#define YIALITE_MOUSE_BUTTON_X1       4
#define YIALITE_MOUSE_BUTTON_X2       5

#define YIALITE_MOUSE_BUTTON_MASK(X)  (1u << ((X)-1))

namespace yialite
{
    typedef uint32_t MouseButtonFlags;
    enum MouseButtonFlags_ : uint32_t
    {
        MOUSE_BUTTON_LMASK =  YIALITE_MOUSE_BUTTON_MASK(YIALITE_MOUSE_BUTTON_LEFT),
        MOUSE_BUTTON_MMASK =  YIALITE_MOUSE_BUTTON_MASK(YIALITE_MOUSE_BUTTON_MIDDLE),
        MOUSE_BUTTON_RMASK =  YIALITE_MOUSE_BUTTON_MASK(YIALITE_MOUSE_BUTTON_RIGHT),
        MOUSE_BUTTON_X1MASK = YIALITE_MOUSE_BUTTON_MASK(YIALITE_MOUSE_BUTTON_X1),
        MOUSE_BUTTON_X2MASK = YIALITE_MOUSE_BUTTON_MASK(YIALITE_MOUSE_BUTTON_X2)
    };
}

#endif