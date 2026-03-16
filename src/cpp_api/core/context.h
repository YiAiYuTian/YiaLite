#ifndef YIALITE_CONTEXT_H
#define YIALITE_CONTEXT_H

#include "../core/core.h"

namespace yialite
{

class Window;
class Renderer;
class Event;
class DevUI;

struct WindowConfig;

struct YIALITE_API Context
{
    Context(const WindowConfig& config);
    ~Context();
    struct Initializer;
    Initializer* initializer = nullptr;
    Window* window = nullptr;
    Renderer* renderer = nullptr;
    Event* event = nullptr;
    DevUI* devui = nullptr;
};

}

#endif