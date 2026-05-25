#include "initialize.h"
#include "logger.h"
#include "../utils/memory/allocator.h"

#include <SDL3/SDL.h>

namespace yialite
{

void* yialiteSDLMalloc(size_t size)
{
    return ALLOCATE_SIZED(size);
}

void* yialiteSDLCalloc(size_t nmemb, size_t size)
{
    void* ptr = ALLOCATE_SIZED(nmemb * size);
    if(ptr){ memset(ptr, 0, nmemb * size); }
    return ptr;
}

void* yialiteSDLRealloc(void *mem, size_t size)
{
    return REALLOCATE_SIZED(mem, size);
}

void yialiteSDLFree(void *mem)
{
    DEALLOCATE(mem);
}

bool init()
{
    bool is_initialized = true;
    
    SDL_SetMemoryFunctions(yialiteSDLMalloc, yialiteSDLCalloc, yialiteSDLRealloc, yialiteSDLFree);
    
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