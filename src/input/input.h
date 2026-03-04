#ifndef INPUT_H
#define INPUT_H

#include "../core/core.h"
#include "../event/mouse_button.h"
#include "scancode.h"

#include <stdint.h>

namespace lite
{

LITE_API bool isKeyPressed(Scancode key);
LITE_API bool isMouseButtonPressed(MouseButtonFlags button, float* x = nullptr, float* y = nullptr);

}

#endif