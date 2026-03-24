#include "initialize.h"
#include "logger.h"

#include <SDL3/SDL.h>

namespace yialite
{

bool init()
{
    bool is_initialized = true;

    if(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        Logger::fatal("Failed to initialize SDL: {}", SDL_GetError());
        is_initialized = false;
    }

    if(!is_initialized)
    {
        SDL_Quit();
    }

    return is_initialized;
}

void quit()
{
    SDL_Quit();
}

}