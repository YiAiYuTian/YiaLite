#include "pch.h"
#include "context.h"
#include "logger.h"
#include "initialize.h"
#include "error.h"
#include "../window/window.h"
#include "../renderer/renderer2d.h"
#include "../event/event.h"
#include "../devui/devui.h"
#include "../utils/memory/allocator.h"

namespace yialite
{

Context::Context(Context&& other) noexcept
    : window(other.window)
    , renderer2d(other.renderer2d)
    , event(other.event)
    , devui(other.devui)
{
    other.window = nullptr;
    other.renderer2d = nullptr;
    other.event = nullptr;
    other.devui = nullptr;
}

Context& Context::operator=(Context&& other) noexcept
{
    if (this != &other)
    {
        DevUI::destroy(devui);
        Event::destroy(event);
        Renderer2D::destroy(renderer2d);
        Window::destroy(window);

        window = other.window;
        renderer2d = other.renderer2d;
        event = other.event;
        devui = other.devui;

        other.window = nullptr;
        other.renderer2d = nullptr;
        other.event = nullptr;
        other.devui = nullptr;
    }
    return *this;
}

Result<Context*> Context::create(const ContextConfig& config)
{
    Context* ctx = ALLOCATE_OBJECT(Context);
    if (!ctx) return Result<Context*>(ErrorCode::OutOfMemory, "Failed to allocate Context");

    // 1. Initialize SDL
    auto init_result = init();
    if (!init_result)
        return Result<Context*>(init_result.error());

    // 2. Create Window
    auto window_result = Window::create(config.window_config);
    if (!window_result)
        return Result<Context*>(window_result.error());
    ctx->window = window_result.value();

    // 3. Create Renderer2D
    auto renderer_result = Renderer2D::create(ctx->window);
    if (!renderer_result)
    {
        Window::destroy(ctx->window);
        return Result<Context*>(renderer_result.error());
    }
    ctx->renderer2d = renderer_result.value();

    // 4. Create Event
	auto event_result = Event::create();
    if (!event_result)
    {
		Renderer2D::destroy(ctx->renderer2d);
		Window::destroy(ctx->window);
		return Result<Context*>(event_result.error());
    }
    ctx->event = event_result.value();

    // 5. Optionally create DevUI
    ctx->devui = nullptr;
    if (config.enable_devui)
    {
        auto dev_result = DevUI::create(ctx->window, ctx->renderer2d);
        if (!dev_result)
        {
			Event::destroy(ctx->event);
			Renderer2D::destroy(ctx->renderer2d);
			Window::destroy(ctx->window);
			return Result<Context*>(dev_result.error());
        }
		ctx->devui = dev_result.value();
        ctx->event->register_devui_event(ctx->devui);
    }

    return ctx;
}

void Context::destroy(Context* context)
{
    DEALLOCATE_OBJECT(Context, context);
}

Context::~Context()
{
    DevUI::destroy(devui);
    Event::destroy(event);
    Renderer2D::destroy(renderer2d);
    Window::destroy(window);
    quit();

    devui = nullptr;
    event = nullptr;
    renderer2d = nullptr;
    window = nullptr;
}

}
