#include "context.h"
#include "logger.h"
#include "initialize.h"
#include "yialite_exception.h"
#include "../event/event.h"
#include "../window/window.h"
#include "../renderer/renderer.h" 
#include "../devui/devui.h"

#include "../devui/imgui/imgui.h"
#include "../devui/imgui/backends/imgui_impl_sdl3.h"
#include "../devui/imgui/backends/imgui_impl_sdlrenderer3.h"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

namespace yialite
{

//window
static SDL_WindowFlags convertToSDLWindowFlags(const WindowFlags flags)
{
    constexpr std::pair<WindowFlags, SDL_WindowFlags> flag_map[] = {
        {WindowFlags_Fullscreen,      SDL_WINDOW_FULLSCREEN},
        {WindowFlags_Borderless,      SDL_WINDOW_BORDERLESS},
        {WindowFlags_Resizable,       SDL_WINDOW_RESIZABLE},
        {WindowFlags_MouseGrabbed,    SDL_WINDOW_MOUSE_GRABBED},
        {WindowFlags_MouseCapture,    SDL_WINDOW_MOUSE_CAPTURE},
        {WindowFlags_KeyboardGrabbed, SDL_WINDOW_KEYBOARD_GRABBED}
    };

    SDL_WindowFlags sdl_flags = 0;
    for (const auto& [lite_flag, sdl_flag] : flag_map)
    {
        if (flags & lite_flag)
            sdl_flags |= sdl_flag;
    }

    return sdl_flags;
}

struct Window::Impl
{
    SDL_Window* window = nullptr;
};

Window::Window(const WindowConfig& config)
{
    m_config = config;
    m_impl = new Window::Impl();

    m_impl->window = SDL_CreateWindow(config.title.c_str(), config.width, config.height, convertToSDLWindowFlags(config.flags));
    if(!m_impl->window)
    {
        delete m_impl;
        throw YiaLite_Exception("Failed to initialize window: " + std::string(SDL_GetError()));
    }

    Logger::info("Window initialized successfully: {}({}, {})", config.title, config.width, config.height);
}

Window::~Window()
{
    if(m_impl) SDL_DestroyWindow(m_impl->window);
    delete m_impl;
}

void Window::setWidth(int width)
{
    m_config.width = width;
    SDL_SetWindowSize(m_impl->window, width, m_config.height);
}

void Window::setHeight(int height)
{
    m_config.height = height;
    SDL_SetWindowSize(m_impl->window, m_config.width, height);
}

//renderer
struct Renderer::Impl
{
    SDL_Renderer* renderer = nullptr;
};

Renderer::Renderer(Window* window)
{
    m_impl = new Renderer::Impl();

    m_impl->renderer = SDL_CreateRenderer(window->m_impl->window, nullptr);
    if(!m_impl->renderer)
    {
        delete m_impl;
        throw YiaLite_Exception("Failed to initialize renderer: " + std::string(SDL_GetError()));
    }
    SDL_SetRenderDrawBlendMode(m_impl->renderer, SDL_BLENDMODE_BLEND);
}

Renderer::~Renderer()
{
    if(m_impl) SDL_DestroyRenderer(m_impl->renderer);
    delete m_impl;
}

void Renderer::beginDraw(const Color& background_color)
{
    SDL_SetRenderDrawColor(m_impl->renderer, background_color.r, background_color.g, background_color.b, background_color.a);
    SDL_RenderClear(m_impl->renderer);
}

void Renderer::beginDrawF(const FColor& background_color)
{
    SDL_SetRenderDrawColorFloat(m_impl->renderer, background_color.r, background_color.g, background_color.b, background_color.a);
    SDL_RenderClear(m_impl->renderer);
}

void Renderer::endDraw()
{
    SDL_RenderPresent(m_impl->renderer);
}

void Renderer::drawPoint(const Vector2f &pos, const Color& color)
{
    SDL_SetRenderDrawColor(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderPoint(m_impl->renderer, pos.x, pos.y);
}

void Renderer::drawPoints(const Vector2f* pos, int count, const Color& color)
{
    SDL_SetRenderDrawColor(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderPoints(m_impl->renderer, reinterpret_cast<const SDL_FPoint*>(pos), count);
}

void Renderer::drawLine(const Vector2f &start, const Vector2f &end, const Color& color)
{
    SDL_SetRenderDrawColor(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderLine(m_impl->renderer, start.x, start.y, end.x, end.y);
}

void Renderer::drawRect(const Vector2f &pos, const Vector2f &size, const Color& color)
{
    SDL_FRect frect = { pos.x, pos.y, size.x, size.y };
    SDL_SetRenderDrawColor(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderRect(m_impl->renderer, &frect);
}

void Renderer::drawRect(const FRect &rect, const Color& color)
{
    SDL_SetRenderDrawColor(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderRect(m_impl->renderer, reinterpret_cast<const SDL_FRect*>(&rect));
}

void Renderer::drawFillRect(const Vector2f &pos, const Vector2f &size, const Color& color)
{
    SDL_FRect frect = { pos.x, pos.y, size.x, size.y };
    SDL_SetRenderDrawColor(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(m_impl->renderer, &frect);
}

void Renderer::drawFillRect(const FRect &rect, const Color& color)
{
    SDL_SetRenderDrawColor(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(m_impl->renderer, reinterpret_cast<const SDL_FRect*>(&rect));
}

void Renderer::drawPointF(const Vector2f &pos, const FColor& color)
{
    SDL_SetRenderDrawColorFloat(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderPoint(m_impl->renderer, pos.x, pos.y);
}

void Renderer::drawPointsF(const Vector2f *pos, int count, const FColor& color)
{
    SDL_SetRenderDrawColorFloat(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderPoints(m_impl->renderer, reinterpret_cast<const SDL_FPoint*>(pos), count);
}

void Renderer::drawLineF(const Vector2f &start, const Vector2f &end, const FColor& color)
{
    SDL_SetRenderDrawColorFloat(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderLine(m_impl->renderer, start.x, start.y, end.x, end.y);
}

void Renderer::drawRectF(const Vector2f &pos, const Vector2f &size, const FColor& color)
{
    SDL_FRect frect = { pos.x, pos.y, size.x, size.y };
    SDL_SetRenderDrawColorFloat(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderRect(m_impl->renderer, &frect);
}

void Renderer::drawRectF(const FRect &rect, const FColor& color)
{
    SDL_SetRenderDrawColorFloat(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderRect(m_impl->renderer, reinterpret_cast<const SDL_FRect*>(&rect));
}

void Renderer::drawFillRectF(const Vector2f &pos, const Vector2f &size, const FColor& color)
{
    SDL_FRect frect = { pos.x, pos.y, size.x, size.y };
    SDL_SetRenderDrawColorFloat(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(m_impl->renderer, &frect);
}

void Renderer::drawFillRectF(const FRect &rect, const FColor& color)
{
    SDL_SetRenderDrawColorFloat(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(m_impl->renderer, reinterpret_cast<const SDL_FRect*>(&rect));
}

//devui
struct DevUI::Impl
{
    SDL_Renderer* sdl_renderer = nullptr;

    void processEvent(const SDL_Event& sdl_event)
    {
        ImGui_ImplSDL3_ProcessEvent(&sdl_event);
    }
};

DevUI::DevUI(Window* window, Renderer* renderer)
{
    m_impl = new DevUI::Impl();
    m_impl->sdl_renderer = renderer->m_impl->renderer;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForSDLRenderer(window->m_impl->window, renderer->m_impl->renderer);
    ImGui_ImplSDLRenderer3_Init(renderer->m_impl->renderer);
}

DevUI::~DevUI()
{
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    delete m_impl;
}

void DevUI::onUpdate()
{
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void DevUI::onRender()
{
    auto& renderer = m_impl->sdl_renderer;
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    SDL_SetRenderScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    
    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
}

//event
struct Event::Impl
{
    SDL_Event event;

    DevUI* devui = nullptr;

    void* data = nullptr;

    QuitEventCallback quit_event_callback = nullptr;
    KeyEventCallback key_event_callback = nullptr;
    MouseButtonEventCallback mouse_event_callback = nullptr;
    MouseWheelEventCallback mouse_wheel_event_callback = nullptr;
    MouseMotionEventCallback mouse_motion_event_callback = nullptr;
    WindowResizedEventCallback window_resized_event_callback = nullptr;
    WindowMovedEventCallback window_moved_event_callback = nullptr;
    WindowFocusGainedEventCallback window_focus_gained_event_callback = nullptr;
    WindowFocusLostEventCallback window_focus_lost_event_callback = nullptr;
};

Event::Event()
{
    m_impl = new Event::Impl();
}

Event::~Event()
{
    delete m_impl;
}

void Event::onUpdate()
{
    auto& sdl_event = m_impl->event;
    while (SDL_PollEvent(&sdl_event))
    {
        if(m_impl->devui)
            m_impl->devui->m_impl->processEvent(sdl_event);

        switch (sdl_event.type)
        {
        case SDL_EVENT_QUIT:
            if(m_impl->quit_event_callback) 
                m_impl->quit_event_callback(m_impl->data);
            break;
        case SDL_EVENT_KEY_DOWN:
            if(m_impl->key_event_callback)
            {
                m_impl->key_event_callback(
                    sdl_event.key.key,
                    sdl_event.key.repeat,
                    sdl_event.key.down,
                    sdl_event.key.mod,
                    m_impl->data
                );
            }
            break;
        case SDL_EVENT_KEY_UP:
            if(m_impl->key_event_callback)
            {
                m_impl->key_event_callback(
                    sdl_event.key.key,
                    sdl_event.key.repeat,
                    sdl_event.key.down,
                    sdl_event.key.mod,
                    m_impl->data
                );
            }
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if(m_impl->mouse_event_callback)
            {
                m_impl->mouse_event_callback(
                    sdl_event.button.button,
                    sdl_event.button.x,
                    sdl_event.button.y,
                    sdl_event.button.down,
                    sdl_event.button.clicks,
                    m_impl->data
                );
            }
            break;
        case SDL_EVENT_MOUSE_BUTTON_UP:
            if(m_impl->mouse_event_callback)
            {
                m_impl->mouse_event_callback(
                    sdl_event.button.button,
                    sdl_event.button.x,
                    sdl_event.button.y,
                    sdl_event.button.down,
                    sdl_event.button.clicks,
                    m_impl->data
                );
            }
            break;
        case SDL_EVENT_MOUSE_WHEEL:
            if(m_impl->mouse_wheel_event_callback)
            {
                m_impl->mouse_wheel_event_callback(
                    sdl_event.wheel.x,
                    sdl_event.wheel.y,
                    sdl_event.wheel.mouse_x,
                    sdl_event.wheel.mouse_y,
                    m_impl->data
                );
            }
            break;
        case SDL_EVENT_MOUSE_MOTION:
            if(m_impl->mouse_motion_event_callback)
            {
                m_impl->mouse_motion_event_callback(
                    sdl_event.motion.x,
                    sdl_event.motion.y,
                    sdl_event.motion.xrel,
                    sdl_event.motion.yrel,
                    sdl_event.motion.state,
                    m_impl->data
                );
            }
            break;
        case SDL_EVENT_WINDOW_RESIZED:
            if(m_impl->window_resized_event_callback)
            {
                m_impl->window_resized_event_callback(
                    sdl_event.window.data1,
                    sdl_event.window.data2,
                    m_impl->data
                );
            }
            break;
        case SDL_EVENT_WINDOW_MOVED:
            if(m_impl->window_moved_event_callback)
            {
                m_impl->window_moved_event_callback(
                    sdl_event.window.data1,
                    sdl_event.window.data2,
                    m_impl->data
                );
            }
            break;
        case SDL_EVENT_WINDOW_FOCUS_GAINED:
            if(m_impl->window_focus_gained_event_callback)
            {
                m_impl->window_focus_gained_event_callback(
                    m_impl->data
                );
            }
            break;
        case SDL_EVENT_WINDOW_FOCUS_LOST:
            if(m_impl->window_focus_lost_event_callback)
            {
                m_impl->window_focus_lost_event_callback(
                    m_impl->data
                );
            }
            break;
        default:
            break;
        }
    }
}

void Event::setGlobalData(void *data)
{
    m_impl->data = data;
}

void Event::registerDevUIEvent(DevUI* devui)
{
    m_impl->devui = devui;
}

void Event::registerQuitEventCallback(QuitEventCallback callback)
{
    m_impl->quit_event_callback = callback;
}

void Event::registerKeyEventCallback(KeyEventCallback callback)
{
    m_impl->key_event_callback = callback;
}

void Event::registerMouseButtonEventCallback(MouseButtonEventCallback callback)
{
    m_impl->mouse_event_callback = callback;
}

void Event::registerMouseWheelEventCallback(MouseWheelEventCallback callback)
{
    m_impl->mouse_wheel_event_callback = callback;
}

void Event::registerMouseMotionEventCallback(MouseMotionEventCallback callback)
{
    m_impl->mouse_motion_event_callback = callback;
}

void Event::registerWindowResizedEventCallback(WindowResizedEventCallback callback)
{
    m_impl->window_resized_event_callback = callback;
}

void Event::registerWindowMovedEventCallback(WindowMovedEventCallback callback)
{
    m_impl->window_moved_event_callback = callback;
}

void Event::registerWindowFocusGainedEventCallback(WindowFocusGainedEventCallback callback)
{
    m_impl->window_focus_gained_event_callback = callback;
}

void Event::registerWindowFocusLostEventCallback(WindowFocusLostEventCallback callback)
{
    m_impl->window_focus_lost_event_callback = callback;
}

//context
struct Context::Initializer
{
    Initializer()
    {
        if(!init()) throw YiaLite_Exception("Failed to initialize Lite");
    }

    ~Initializer()
    {
        quit();
    }
};

Context::Context(const ContextConfig &config)
{
    initializer = new Initializer();
    window = new Window(config.window_config);
    renderer = new Renderer(window);
    event = new Event();
    devui = nullptr;
    
    if(config.enable_devui)
    {
        devui = new DevUI(window, renderer);
        event->registerDevUIEvent(devui);
    }
}

Context::~Context()
{
    delete devui;
    delete event;
    delete renderer;
    delete window;
    delete initializer;
}

}