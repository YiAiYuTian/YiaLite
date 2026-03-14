#ifndef YIALITE_DEVUI_H
#define YIALITE_DEVUI_H

#include "../core/core.h"

namespace yialite
{

class Window;
class Renderer;
class Event;

class YIALITE_API DevUI
{
    friend class Event;
public:
    DevUI(Window* window, Renderer* renderer);
    ~DevUI();
    DevUI(const DevUI&) = delete;
    DevUI& operator=(const DevUI&) = delete;
    DevUI(DevUI&&) = delete;
    DevUI& operator=(DevUI&&) = delete;

    void onUpdate();
    void onRender();

    void Text(const char *fmt, ...);
private:
    struct Impl;
    Impl* m_impl = nullptr;
};
    
}

#endif