#include "context.h"
#include "logger.h"
#include "initialize.h"
#include "yialite_exception.h"
#include "../window/window.h"
#include "../renderer/renderer2d.h"
#include "../event/event.h"
#include "../devui/devui.h"

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

Context::Context(const ContextConfig &config)
{
    initializer = new Initializer();
    window = new Window(config.window_config);
    renderer2d = new Renderer2D(window);
    event = new Event();
    devui = nullptr;
    
    if(config.enable_devui)
    {
        devui = new DevUI(window, renderer2d);
        event->registerDevUIEvent(devui);
    }
}

Context::~Context()
{
    delete devui;
    delete event;
    delete renderer2d;
    delete window;
    delete initializer;
}

}