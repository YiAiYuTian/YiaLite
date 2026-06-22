#include "pch.h"
#include "input.h"

#include <SDL3/SDL.h>

namespace yialite
{

bool is_key_pressed(Scancode key)
{
    auto* keyboard = SDL_GetKeyboardState(nullptr);
    if (!keyboard) return false;
    
    return keyboard[key];
}

bool is_mouse_button_pressed(MouseButtonFlags button, float* x, float* y)
{
    SDL_MouseButtonFlags button_flag = SDL_GetMouseState(x, y);

    return (button_flag & button) != 0;
}

}

