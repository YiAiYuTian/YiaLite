#ifndef YIALITE_DEVUI_H
#define YIALITE_DEVUI_H

#include "../core/core.h"

namespace yialite
{

class Window;
class Renderer2D;

class YIALITE_API DevUI
{
public:
    DevUI(Window* window, Renderer2D* renderer);
    ~DevUI();
    DevUI(const DevUI&) = delete;
    DevUI& operator=(const DevUI&) = delete;
    DevUI(DevUI&&) = delete;
    DevUI& operator=(DevUI&&) = delete;

    void onUpdate();
    void onRender();
private:
    struct Impl;
    Impl* m_impl = nullptr;
};

}


#endif