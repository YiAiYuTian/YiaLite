#ifndef CONTEXT_H
#define CONTEXT_H

#include "../core/core.h"

namespace lite
{

class Window;
class Renderer;

struct WindowConfig;

struct LITE_API Context
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