#include "context.h"
#include "logger.h"
#include "initialize.h"
#include "yialite_exception.h"
#include "../window/window.h"
#include "../renderer/renderer2d.h"
#include "../event/event.h"
#include "../devui/devui.h"
#include "../utils/memory/allocator.h"

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
    initializer =   ALLOCATE_OBJECT(Initializer);
    window =        ALLOCATE_OBJECT(Window, config.window_config);
    renderer2d =    ALLOCATE_OBJECT(Renderer2D, window);
    event =         ALLOCATE_OBJECT(Event);
    devui =         nullptr;
    
    if(config.enable_devui)
    {
        devui = ALLOCATE_OBJECT(DevUI, window, renderer2d);
        event->registerDevUIEvent(devui);
    }
}

Context::~Context()
{
    DEALLOCATE_OBJECT(DevUI, devui);
    DEALLOCATE_OBJECT(Event, event);
    DEALLOCATE_OBJECT(Renderer2D, renderer2d);
    DEALLOCATE_OBJECT(Window, window);
    DEALLOCATE_OBJECT(Initializer, initializer);
}

}