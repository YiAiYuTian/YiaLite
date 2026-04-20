#ifndef YIALITE_CONTEXT_H
#define YIALITE_CONTEXT_H

#include "core.h"
#include "config.h"

namespace yialite
{

class Window;
class Renderer2D;
class Event;
class DevUI;

struct YIALITE_API Context
{
    Context(const ContextConfig& config);
    ~Context();
    struct Initializer;
    Initializer* initializer = nullptr;
    Window* window = nullptr;
    Renderer2D* renderer2d = nullptr;
    Event* event = nullptr;
    DevUI* devui = nullptr;
};

}

#endif