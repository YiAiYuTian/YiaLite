#ifndef YIALITE_CONTEXT_H
#define YIALITE_CONTEXT_H

#include "core.h"
#include "config.h"
#include "result.h"

namespace yialite
{

class Window;
class EventManager;
class Renderer2D;
class DevUI;

class YIALITE_API Context
{
public:
    ~Context();
    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;
    Context(Context&& other) noexcept;
    Context& operator=(Context&& other) noexcept;

    static Result<Context*> create(const ContextConfig& config);
    static void destroy(Context* context);

    Window* window = nullptr;
    Renderer2D* renderer2d = nullptr;
    EventManager* event = nullptr;
    DevUI* devui = nullptr;
private:
    Context() = default;
};

}

#endif
