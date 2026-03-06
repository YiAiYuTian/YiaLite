#ifndef C_YIALITE_INPUT_H
#define C_YIALITE_INPUT_H

#include "../../src/core/core.h"

#include "../event/mouse_button.h"
#include "scancode.h"

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

YIALITE_API bool YiaLite_isKeyPressed(YiaLite_Scancode key);
YIALITE_API bool YiaLite_isMouseButtonPressed(YiaLite_MouseButtonFlags button, float* x, float* y);

#ifdef __cplusplus
}
#endif

#endif