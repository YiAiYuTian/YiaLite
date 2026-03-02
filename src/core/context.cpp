#include "context.h"
#include "lite_exception.h"
#include "initialize.h"
#include "../window/window.h"
#include "../renderer/renderer.h" 

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

namespace lite
{

struct Context::Initializer
{
    Initializer()
    {
        if(!initLite()) throw Lite_Exception("Failed to initialize Lite");
    }

    ~Initializer()
    {
        quitLite();
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