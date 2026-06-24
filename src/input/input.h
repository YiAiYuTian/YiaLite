#ifndef YIALITE_INPUT_H
#define YIALITE_INPUT_H

#include "../core/core.h"
#include "../event/mouse_button.h"
#include "scancode.h"

namespace yialite
{

YIALITE_API bool is_key_pressed(Scancode key);
YIALITE_API bool is_mouse_button_pressed(MouseButtonFlags_ button, float* x = nullptr, float* y = nullptr);
YIALITE_API bool is_mouse_button_pressed(MouseButtonFlags button, float* x = nullptr, float* y = nullptr);

}

#endif