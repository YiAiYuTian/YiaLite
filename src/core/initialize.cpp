#include "initialize.h"
#include "log.h"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

namespace lite
{

LITE_API bool initLite()
{
    bool is_initialized = true;

    if(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        LOG_FATAL("Failed to initialize SDL: {}", SDL_GetError());
        is_initialized = false;
    }
    
    if(!TTF_Init())
    {
        LOG_FATAL("Failed to initialize SDL_ttf: {}", SDL_GetError());
        is_initialized = false;
    }

    if(!is_initialized)
    {
        TTF_Quit();
        SDL_Quit();
    }

    return is_initialized;
}

LITE_API void quitLite()
{
    TTF_Quit();
    SDL_Quit();
}

}