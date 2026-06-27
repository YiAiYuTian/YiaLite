#ifndef YIALITE_DEVUI_H
#define YIALITE_DEVUI_H

#include "../core/core.h"
#include "../core/result.h"

namespace yialite
{

class IWindow;
class Renderer2D;

class YIALITE_API DevUI
{
    FRIEND_ALLOCATOR
public:
    ~DevUI();
    DevUI(const DevUI&) = delete;
    DevUI& operator=(const DevUI&) = delete;
    DevUI(DevUI&&) = delete;
    DevUI& operator=(DevUI&&) = delete;

    static Result<DevUI*> create(IWindow* window, Renderer2D* renderer);
    static void destroy(DevUI* devui);

    void on_update();
    void on_render();
private:
    DevUI() = default;
    struct Impl;
    Impl* m_impl = nullptr;
};

}

#endif
