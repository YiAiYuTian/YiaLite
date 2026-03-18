#include "context.h"
#include "logger.h"
#include "initialize.h"
#include "yialite_exception.h"
#include "../event/event.h"
#include "../window/window.h"
#include "../renderer/renderer2d.h"
#include "../devui/devui.h"

#include "../devui/imgui/imgui.h"
#include "../devui/imgui/backends/imgui_impl_sdl3.h"
#include "../devui/imgui/backends/imgui_impl_sdlrenderer3.h"

#include <deque>
#include <vector>
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
static void colorToSDLFColor(const Color& color, SDL_FColor& out_fcolor)
{
    out_fcolor.r = color.r / 255.0f;
    out_fcolor.g = color.g / 255.0f;
    out_fcolor.b = color.b / 255.0f;
    out_fcolor.a = color.a / 255.0f;
}

static void fcolorToSDLFColor(const FColor& fcolor, SDL_FColor& out_fcolor)
{
    out_fcolor.r = fcolor.r;
    out_fcolor.g = fcolor.g;
    out_fcolor.b = fcolor.b;
    out_fcolor.a = fcolor.a;
}

struct Renderer2DCommand
{
    std::vector<SDL_Vertex> vertices;
    SDL_Texture* texture = nullptr;
};

class Renderer2DCommandPool
{
public:
    Renderer2DCommandPool(size_t initial_size = 256)
    {
        m_pool.resize(initial_size);
        m_free_commands.reserve(initial_size);

        for(size_t i = 0; i < initial_size; ++i)
        {
            auto& cmd = m_pool[i];
            cmd.vertices.reserve(4);
            m_free_commands.push_back(&cmd);
        }
    }

    Renderer2DCommand* allocate()
    {
        if(m_free_commands.empty())
        {
            m_pool.emplace_back();
            auto& new_cmd = m_pool.back();
            new_cmd.vertices.reserve(4);
            m_free_commands.push_back(&new_cmd);
        }

        Renderer2DCommand* cmd = m_free_commands.back();
        cmd->vertices.clear();
        cmd->texture = nullptr;

        m_free_commands.pop_back();
        m_used_commands.push_back(cmd);

        return cmd;
    }

    void resetFrame()
    {
        m_free_commands.insert(m_free_commands.end(), m_used_commands.begin(), m_used_commands.end());
        m_used_commands.clear();
    }
private:
    std::deque<Renderer2DCommand> m_pool;
    std::vector<Renderer2DCommand*> m_free_commands;
    std::vector<Renderer2DCommand*> m_used_commands;
};

struct Renderer2D::Impl
{
    SDL_Renderer* renderer = nullptr;
    std::vector<Renderer2DCommand*> render_commands;
    Renderer2DCommandPool command_pool;
};

Renderer2D::Renderer2D(Window* window)
{
    m_impl = new Renderer2D::Impl();

    m_impl->renderer = SDL_CreateRenderer(window->m_impl->window, nullptr);
    if(!m_impl->renderer)
    {
        delete m_impl;
        throw YiaLite_Exception("Failed to initialize renderer: " + std::string(SDL_GetError()));
    }
    SDL_SetRenderDrawBlendMode(m_impl->renderer, SDL_BLENDMODE_BLEND);
}

Renderer2D::~Renderer2D()
{
    if(m_impl) SDL_DestroyRenderer(m_impl->renderer);
    delete m_impl;
}

void Renderer2D::beginDraw(const Color& background_color)
{
    SDL_SetRenderDrawColor(m_impl->renderer, background_color.r, background_color.g, background_color.b, background_color.a);
    SDL_RenderClear(m_impl->renderer);
}

void Renderer2D::beginDrawF(const FColor& background_color)
{
    SDL_SetRenderDrawColorFloat(m_impl->renderer, background_color.r, background_color.g, background_color.b, background_color.a);
    SDL_RenderClear(m_impl->renderer);
}

void Renderer2D::endDraw()
{
    static std::vector<SDL_Vertex> batch_vertices;
    static SDL_Texture* batch_texture;
    if(batch_vertices.capacity() == 0) batch_vertices.reserve(1024 * 10);
    batch_vertices.clear();
    batch_texture = nullptr;

    for(auto& cmd : m_impl->render_commands)
    {
        SDL_RenderGeometry(
            m_impl->renderer,
            cmd->texture,
            cmd->vertices.data(),
            static_cast<int>(cmd->vertices.size()),
            nullptr,
            0
        );
    }
/*
    for(auto& cmd : m_impl->render_commands)
    {
        if(cmd->texture != batch_texture)
        {
            if(!batch_vertices.empty())
            {
                SDL_RenderGeometry(
                    m_impl->renderer,
                    batch_texture,
                    batch_vertices.data(),
                    static_cast<int>(batch_vertices.size()),
                    nullptr,
                    0
                );
                batch_vertices.clear();
            }
            batch_texture = cmd->texture;
        }

        batch_vertices.insert(batch_vertices.end(), cmd->vertices.begin(), cmd->vertices.end());
    }

    if(!batch_vertices.empty())
    {
        SDL_RenderGeometry(
            m_impl->renderer,
            batch_texture,
            batch_vertices.data(),
            static_cast<int>(batch_vertices.size()),
            nullptr,
            0
        );
    }
*/
    SDL_RenderPresent(m_impl->renderer);

    m_impl->render_commands.clear();
    m_impl->command_pool.resetFrame();
}

void Renderer2D::drawPoint(const Vector2f &pos, const Color& color)
{
    SDL_SetRenderDrawColor(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderPoint(m_impl->renderer, pos.x, pos.y);

    Renderer2DCommand* cmd = m_impl->command_pool.allocate();
    SDL_FColor sdl_fcolor;
    colorToSDLFColor(color, sdl_fcolor);
    
    cmd->vertices.emplace_back(SDL_Vertex{
        { pos.x, pos.y },
        sdl_fcolor,
        { 0.0f, 0.0f }
    });

    m_impl->render_commands.push_back(cmd);
}

void Renderer2D::drawPoints(const Vector2f* pos, int count, const Color& color)
{
    SDL_SetRenderDrawColor(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderPoints(m_impl->renderer, reinterpret_cast<const SDL_FPoint*>(pos), count);
}

void Renderer2D::drawLine(const Vector2f &start, const Vector2f &end, const Color& color)
{
    SDL_SetRenderDrawColor(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderLine(m_impl->renderer, start.x, start.y, end.x, end.y);
}

void Renderer2D::drawRect(const Vector2f &pos, const Vector2f &size, const Color& color)
{
    Renderer2DCommand* cmd = m_impl->command_pool.allocate();
    SDL_FColor sdl_fcolor;
    colorToSDLFColor(color, sdl_fcolor);

    float x1 = pos.x;
    float y1 = pos.y;
    float x2 = pos.x + size.x;
    float y2 = pos.y + size.y;

    cmd->vertices.emplace_back(SDL_Vertex{{x1, y1}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x2, y1}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x2, y2}, sdl_fcolor, {0,0}});

    cmd->vertices.emplace_back(SDL_Vertex{{x1, y1}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x2, y2}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x1, y2}, sdl_fcolor, {0,0}});

    m_impl->render_commands.push_back(cmd);
}

void Renderer2D::drawRect(const FRect &rect, const Color& color)
{
    Renderer2DCommand* cmd = m_impl->command_pool.allocate();
    SDL_FColor sdl_fcolor;
    colorToSDLFColor(color, sdl_fcolor);

    float x1 = rect.x;
    float y1 = rect.y;
    float x2 = rect.x + rect.w;
    float y2 = rect.y + rect.h;

    cmd->vertices.emplace_back(SDL_Vertex{{x1, y1}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x2, y1}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x2, y2}, sdl_fcolor, {0,0}});

    cmd->vertices.emplace_back(SDL_Vertex{{x1, y1}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x2, y2}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x1, y2}, sdl_fcolor, {0,0}});

    m_impl->render_commands.push_back(cmd);
}

void Renderer2D::drawFillRect(const Vector2f &pos, const Vector2f &size, const Color& color)
{
    Renderer2DCommand* cmd = m_impl->command_pool.allocate();
    SDL_FColor sdl_fcolor;
    colorToSDLFColor(color, sdl_fcolor);

    float x1 = pos.x;
    float y1 = pos.y;
    float x2 = pos.x + size.x;
    float y2 = pos.y + size.y;

    cmd->vertices.emplace_back(SDL_Vertex{{x1, y1}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x2, y1}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x2, y2}, sdl_fcolor, {0,0}});

    cmd->vertices.emplace_back(SDL_Vertex{{x1, y1}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x2, y2}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x1, y2}, sdl_fcolor, {0,0}});

    m_impl->render_commands.push_back(cmd);
}

void Renderer2D::drawFillRect(const FRect &rect, const Color& color)
{
    Renderer2DCommand* cmd = m_impl->command_pool.allocate();
    SDL_FColor sdl_fcolor;
    colorToSDLFColor(color, sdl_fcolor);

    float x1 = rect.x;
    float y1 = rect.y;
    float x2 = rect.x + rect.w;
    float y2 = rect.y + rect.h;

    cmd->vertices.emplace_back(SDL_Vertex{{x1, y1}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x2, y1}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x2, y2}, sdl_fcolor, {0,0}});

    cmd->vertices.emplace_back(SDL_Vertex{{x1, y1}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x2, y2}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x1, y2}, sdl_fcolor, {0,0}});

    m_impl->render_commands.push_back(cmd);
}

void Renderer2D::drawPointF(const Vector2f &pos, const FColor& color)
{
    SDL_SetRenderDrawColorFloat(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderPoint(m_impl->renderer, pos.x, pos.y);
}

void Renderer2D::drawPointsF(const Vector2f *pos, int count, const FColor& color)
{
    SDL_SetRenderDrawColorFloat(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderPoints(m_impl->renderer, reinterpret_cast<const SDL_FPoint*>(pos), count);
}

void Renderer2D::drawLineF(const Vector2f &start, const Vector2f &end, const FColor& color)
{
    SDL_SetRenderDrawColorFloat(m_impl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderLine(m_impl->renderer, start.x, start.y, end.x, end.y);
}

void Renderer2D::drawRectF(const Vector2f &pos, const Vector2f &size, const FColor& color)
{
    Renderer2DCommand* cmd = m_impl->command_pool.allocate();
    SDL_FColor sdl_fcolor;
    fcolorToSDLFColor(color, sdl_fcolor);

    float x1 = pos.x;
    float y1 = pos.y;
    float x2 = pos.x + size.x;
    float y2 = pos.y + size.y;

    cmd->vertices.emplace_back(SDL_Vertex{{x1, y1}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x2, y1}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x2, y2}, sdl_fcolor, {0,0}});

    cmd->vertices.emplace_back(SDL_Vertex{{x1, y1}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x2, y2}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x1, y2}, sdl_fcolor, {0,0}});

    m_impl->render_commands.push_back(cmd);
}

void Renderer2D::drawRectF(const FRect &rect, const FColor& color)
{
    Renderer2DCommand* cmd = m_impl->command_pool.allocate();
    SDL_FColor sdl_fcolor;
    fcolorToSDLFColor(color, sdl_fcolor);

    float x1 = rect.x;
    float y1 = rect.y;
    float x2 = rect.x + rect.w;
    float y2 = rect.y + rect.h;

    cmd->vertices.emplace_back(SDL_Vertex{{x1, y1}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x2, y1}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x2, y2}, sdl_fcolor, {0,0}});

    cmd->vertices.emplace_back(SDL_Vertex{{x1, y1}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x2, y2}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x1, y2}, sdl_fcolor, {0,0}});

    m_impl->render_commands.push_back(cmd);
}

void Renderer2D::drawFillRectF(const Vector2f &pos, const Vector2f &size, const FColor& color)
{
    Renderer2DCommand* cmd = m_impl->command_pool.allocate();
    SDL_FColor sdl_fcolor;
    fcolorToSDLFColor(color, sdl_fcolor);

    float x1 = pos.x;
    float y1 = pos.y;
    float x2 = pos.x + size.x;
    float y2 = pos.y + size.y;

    cmd->vertices.emplace_back(SDL_Vertex{{x1, y1}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x2, y1}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x2, y2}, sdl_fcolor, {0,0}});

    cmd->vertices.emplace_back(SDL_Vertex{{x1, y1}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x2, y2}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x1, y2}, sdl_fcolor, {0,0}});

    m_impl->render_commands.push_back(cmd);
}

void Renderer2D::drawFillRectF(const FRect &rect, const FColor& color)
{
    Renderer2DCommand* cmd = m_impl->command_pool.allocate();
    SDL_FColor sdl_fcolor;
    fcolorToSDLFColor(color, sdl_fcolor);

    float x1 = rect.x;
    float y1 = rect.y;
    float x2 = rect.x + rect.w;
    float y2 = rect.y + rect.h;

    cmd->vertices.emplace_back(SDL_Vertex{{x1, y1}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x2, y1}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x2, y2}, sdl_fcolor, {0,0}});

    cmd->vertices.emplace_back(SDL_Vertex{{x1, y1}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x2, y2}, sdl_fcolor, {0,0}});
    cmd->vertices.emplace_back(SDL_Vertex{{x1, y2}, sdl_fcolor, {0,0}});

    m_impl->render_commands.push_back(cmd);
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

DevUI::DevUI(Window* window, Renderer2D* renderer2d)
{
    m_impl = new DevUI::Impl();
    m_impl->sdl_renderer = renderer2d->m_impl->renderer;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForSDLRenderer(window->m_impl->window, renderer2d->m_impl->renderer);
    ImGui_ImplSDLRenderer3_Init(renderer2d->m_impl->renderer);
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
    renderer2d = new Renderer2D(window);
    event = new Event();
    devui = nullptr;
    
    if(config.enable_devui)
    {
        devui = new DevUI(window, renderer2d);
        event->registerDevUIEvent(devui);
    }
}

Context::~Context()
{
    delete devui;
    delete event;
    delete renderer2d;
    delete window;
    delete initializer;
}

}