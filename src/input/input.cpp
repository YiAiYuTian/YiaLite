#include "input.h"

#include <SDL3/SDL.h>

namespace lite
{

bool isKeyPressed(Scancode key)
{
    auto* keyboard = SDL_GetKeyboardState(nullptr);
    if (!keyboard) return false;
    
    return keyboard[key];
}

LITE_API bool isMouseButtonPressed(MouseButtonFlags button, float* x, float* y)
{
    SDL_MouseButtonFlags button_flag = SDL_GetMouseState(x, y);

    return (button_flag & button) != 0;
}

}

