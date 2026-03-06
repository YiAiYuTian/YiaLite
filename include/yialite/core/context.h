#ifndef CONTEXT_H
#define CONTEXT_H

#include "../core/core.h"

namespace yialite
{

class Window;
class Renderer;

struct WindowConfig;

struct YIALITE_API Context
{
    Context(const WindowConfig& config);
    ~Context();
    struct Initializer;
    Initializer* initializer;
    Window* window;
    Renderer* renderer;
};

}

#endif