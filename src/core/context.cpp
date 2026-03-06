#include "context.h"
#include "yialite_exception.h"
#include "initialize.h"
#include "../window/window.h"
#include "../renderer/renderer.h" 

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

namespace yialite
{

struct Context::Initializer
{
    Initializer()
    {
        if(!init()) throw YiaLite_Exception("Failed to initialize Lite");
    }

    ~Initializer()
    {
        quit();
    }
};

Context::Context(const WindowConfig &config)
{
    initializer = new Initializer();
    window = new Window(config);
    renderer = new Renderer(window);
}

Context::~Context()
{
    delete renderer;
    delete window;
    delete initializer;
}

}