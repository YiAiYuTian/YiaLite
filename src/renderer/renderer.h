#ifndef RENDERER_H
#define RENDERER_H

#include "../core/core.h"

namespace lite
{

class Window;

class LITE_API Renderer
{
public:
    Renderer(Window* window);
    ~Renderer();

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&&) = delete;
private:
    struct Impl;
    Impl* m_impl = nullptr;
};

}

#endif