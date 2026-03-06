#ifndef YIALITE_INPUT_H
#define YIALITE_INPUT_H

#include "../core/core.h"
#include "../event/mouse_button.h"
#include "scancode.h"

#include <stdint.h>

namespace yialite
{

YIALITE_API bool isKeyPressed(Scancode key);
YIALITE_API bool isMouseButtonPressed(MouseButtonFlags button, float* x = nullptr, float* y = nullptr);

}

#endif