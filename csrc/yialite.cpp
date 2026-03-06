#include "yialite.h"

#include "../src/window/window.h"
#include "../src/renderer/renderer.h"
#include "../src/audio/audio_manager.h" 
#include "../src/event/event.h"
#include "../src/input/input.h"
#include "../src/core/logger.h"
#include "../src/core/log.h"
#include "../src/core/initialize.h"
#include "../src/core/yialite_exception.h"

//window
struct YiaLite_Window
{
    yialite::Window* cpp_window = nullptr;
};

YiaLite_Window* YiaLite_CreateWindow(const YiaLite_WindowConfig* config)
{
    yialite::WindowConfig windowConfig;
    windowConfig.title = config->title ? config->title : "YiaLite Window";
    windowConfig.width = config->width > 0 ? config->width : 1280;
    windowConfig.height = config->height > 0 ? config->height : 720;
    windowConfig.flags = (yialite::WindowFlags)config->flags;

    YiaLite_Window* window = nullptr;
    try
    {
        window = new YiaLite_Window();
        window->cpp_window = new yialite::Window(windowConfig);
    }
    catch(const yialite::YiaLite_Exception& e)
    {
        yialite::Logger::error("{}", e.what());
        delete window;
        return NULL;
    }
    catch(const std::exception& e)
    {
        yialite::Logger::error("Failed to create window: {}", e.what());
        delete window;
        return NULL;
    }

    return window;
}

void YiaLite_DestroyWindow(YiaLite_Window* window)
{
    if(window) delete window->cpp_window;
    delete window;
}

YiaLite_WindowConfig YiaLite_GetWindowConfig(YiaLite_Window *window)
{
    yialite::WindowConfig config = window->cpp_window->getConfig();
    YiaLite_WindowConfig yialite_config;

    yialite_config.title = config.title.c_str();
    yialite_config.width = config.width;
    yialite_config.height = config.height;
    yialite_config.flags = (YiaLite_WindowFlags)config.flags;

    return yialite_config;
}

void YiaLite_SetWindowWidth(YiaLite_Window* window, int width)
{
    window->cpp_window->setWidth(width);
}

void YiaLite_SetWindowHeight(YiaLite_Window *window, int height)
{
    window->cpp_window->setHeight(height);
}

//renderer
struct YiaLite_Renderer
{
    yialite::Renderer* cpp_renderer = nullptr;
};

YiaLite_Renderer *YiaLite_CreateRenderer(YiaLite_Window *window)
{
    yialite::Window* cpp_window = window->cpp_window;

    YiaLite_Renderer* renderer = nullptr;
    try
    {
        renderer = new YiaLite_Renderer();
        renderer->cpp_renderer = new yialite::Renderer(cpp_window);
    }
    catch(const yialite::YiaLite_Exception& e)
    {
        yialite::Logger::error("{}", e.what());
        delete renderer;
        return NULL;
    }
    catch(const std::exception& e)
    {
        yialite::Logger::error("Failed to create renderer: {}", e.what());
        delete renderer;
        return NULL;
    }
    
    return renderer;
}

void YiaLite_DestroyRenderer(YiaLite_Renderer* renderer)
{
    if(renderer) delete renderer->cpp_renderer;
    delete renderer;
}

void YiaLite_BeginDraw(YiaLite_Renderer* renderer, const YiaLite_Color background_color)
{
    const yialite::Color& cpp_color = *reinterpret_cast<const yialite::Color*>(&background_color);
    renderer->cpp_renderer->beginDraw(cpp_color);
}

void YiaLite_BeginDrawF(YiaLite_Renderer* renderer, const YiaLite_FColor background_fcolor)
{
    const yialite::FColor& cpp_fcolor = *reinterpret_cast<const yialite::FColor*>(&background_fcolor);
    renderer->cpp_renderer->beginDrawF(cpp_fcolor);
}

void YiaLite_EndDraw(YiaLite_Renderer* renderer)
{
    renderer->cpp_renderer->endDraw();
}

void YiaLite_DrawPoint(YiaLite_Renderer* renderer, const YiaLite_Vector2f pos, const YiaLite_Color color)
{
    const yialite::Vector2f& cpp_pos = *reinterpret_cast<const yialite::Vector2f*>(&pos);
    const yialite::Color& cpp_color = *reinterpret_cast<const yialite::Color*>(&color);
    renderer->cpp_renderer->drawPoint(cpp_pos, cpp_color);
}

void YiaLite_DrawPoints(YiaLite_Renderer* renderer, const YiaLite_Vector2f* pos, int count, const YiaLite_Color color)
{
    const yialite::Vector2f* cpp_pos = reinterpret_cast<const yialite::Vector2f*>(pos);
    const yialite::Color& cpp_color = *reinterpret_cast<const yialite::Color*>(&color);
    renderer->cpp_renderer->drawPoints(cpp_pos, count, cpp_color);
}

void YiaLite_DrawLine(YiaLite_Renderer* renderer, const YiaLite_Vector2f start, const YiaLite_Vector2f end, const YiaLite_Color color)
{
    const yialite::Vector2f& cpp_start = *reinterpret_cast<const yialite::Vector2f*>(&start);
    const yialite::Vector2f& cpp_end = *reinterpret_cast<const yialite::Vector2f*>(&end);
    const yialite::Color& cpp_color = *reinterpret_cast<const yialite::Color*>(&color);
    renderer->cpp_renderer->drawLine(cpp_start, cpp_end, cpp_color);
}

void YiaLite_DrawRectV(YiaLite_Renderer* renderer, const YiaLite_Vector2f pos, const YiaLite_Vector2f size, const YiaLite_Color color)
{
    const yialite::Vector2f& cpp_pos = *reinterpret_cast<const yialite::Vector2f*>(&pos);
    const yialite::Vector2f& cpp_size = *reinterpret_cast<const yialite::Vector2f*>(&size);
    const yialite::Color& cpp_color = *reinterpret_cast<const yialite::Color*>(&color);
    renderer->cpp_renderer->drawRect(cpp_pos, cpp_size, cpp_color);
}

void YiaLite_DrawRectR(YiaLite_Renderer* renderer, const YiaLite_FRect rect, const YiaLite_Color color)
{
    const yialite::FRect& cpp_rect = *reinterpret_cast<const yialite::FRect*>(&rect);
    const yialite::Color& cpp_color = *reinterpret_cast<const yialite::Color*>(&color);
    renderer->cpp_renderer->drawRect(cpp_rect, cpp_color);
}

void YiaLite_DrawFillRectV(YiaLite_Renderer* renderer, const YiaLite_Vector2f pos, const YiaLite_Vector2f size, const YiaLite_Color color)
{
    const yialite::Vector2f& cpp_pos = *reinterpret_cast<const yialite::Vector2f*>(&pos);
    const yialite::Vector2f& cpp_size = *reinterpret_cast<const yialite::Vector2f*>(&size);
    const yialite::Color& cpp_color = *reinterpret_cast<const yialite::Color*>(&color);
    renderer->cpp_renderer->drawFillRect(cpp_pos, cpp_size, cpp_color);
}

void YiaLite_DrawFillRectR(YiaLite_Renderer* renderer, const YiaLite_FRect rect, const YiaLite_Color color)
{
    const yialite::FRect& cpp_rect = *reinterpret_cast<const yialite::FRect*>(&rect);
    const yialite::Color& cpp_color = *reinterpret_cast<const yialite::Color*>(&color);
    renderer->cpp_renderer->drawFillRect(cpp_rect, cpp_color);
}

void YiaLite_DrawPointF(YiaLite_Renderer* renderer, const YiaLite_Vector2f pos, const YiaLite_FColor fcolor)
{
    const yialite::Vector2f& cpp_pos = *reinterpret_cast<const yialite::Vector2f*>(&pos);
    const yialite::FColor& cpp_fcolor = *reinterpret_cast<const yialite::FColor*>(&fcolor);
    renderer->cpp_renderer->drawPointF(cpp_pos, cpp_fcolor);
}

void YiaLite_DrawPointsF(YiaLite_Renderer* renderer, const YiaLite_Vector2f* pos, int count, const YiaLite_FColor fcolor)
{
    const yialite::Vector2f* cpp_pos = reinterpret_cast<const yialite::Vector2f*>(pos);
    const yialite::FColor& cpp_fcolor = *reinterpret_cast<const yialite::FColor*>(&fcolor);
    renderer->cpp_renderer->drawPointsF(cpp_pos, count, cpp_fcolor);
}

void YiaLite_DrawLineF(YiaLite_Renderer* renderer, const YiaLite_Vector2f start, const YiaLite_Vector2f end, const YiaLite_FColor fcolor)
{
    const yialite::Vector2f& cpp_start = *reinterpret_cast<const yialite::Vector2f*>(&start);
    const yialite::Vector2f& cpp_end = *reinterpret_cast<const yialite::Vector2f*>(&end);
    const yialite::FColor& cpp_fcolor = *reinterpret_cast<const yialite::FColor*>(&fcolor);
    renderer->cpp_renderer->drawLineF(cpp_start, cpp_end, cpp_fcolor);
}

void YiaLite_DrawRectF(YiaLite_Renderer* renderer, const YiaLite_Vector2f pos, const YiaLite_Vector2f size, const YiaLite_FColor fcolor)
{
    const yialite::Vector2f& cpp_pos = *reinterpret_cast<const yialite::Vector2f*>(&pos);
    const yialite::Vector2f& cpp_size = *reinterpret_cast<const yialite::Vector2f*>(&size);
    const yialite::FColor& cpp_fcolor = *reinterpret_cast<const yialite::FColor*>(&fcolor);
    renderer->cpp_renderer->drawRectF(cpp_pos, cpp_size, cpp_fcolor);
}

void YiaLite_DrawRectRF(YiaLite_Renderer* renderer, const YiaLite_FRect rect, const YiaLite_FColor fcolor)
{
    const yialite::FRect& cpp_rect = *reinterpret_cast<const yialite::FRect*>(&rect);
    const yialite::FColor& cpp_fcolor = *reinterpret_cast<const yialite::FColor*>(&fcolor);
    renderer->cpp_renderer->drawRectF(cpp_rect, cpp_fcolor);
}

void YiaLite_DrawFillRectVF(YiaLite_Renderer* renderer, const YiaLite_Vector2f pos, const YiaLite_Vector2f size, const YiaLite_FColor fcolor)
{
    const yialite::Vector2f& cpp_pos = *reinterpret_cast<const yialite::Vector2f*>(&pos);
    const yialite::Vector2f& cpp_size = *reinterpret_cast<const yialite::Vector2f*>(&size);
    const yialite::FColor& cpp_fcolor = *reinterpret_cast<const yialite::FColor*>(&fcolor);
    renderer->cpp_renderer->drawFillRectF(cpp_pos, cpp_size, cpp_fcolor);
}

void YiaLite_DrawFillRectRF(YiaLite_Renderer* renderer, const YiaLite_FRect rect, const YiaLite_FColor fcolor)
{
    const yialite::FRect& cpp_rect = *reinterpret_cast<const yialite::FRect*>(&rect);
    const yialite::FColor& cpp_fcolor = *reinterpret_cast<const yialite::FColor*>(&fcolor);
    renderer->cpp_renderer->drawFillRectF(cpp_rect, cpp_fcolor);
}

// event
struct YiaLite_Event
{
    yialite::Event* cpp_event = nullptr;
};

YiaLite_Event* YiaLite_CreateEvent(void)
{
    YiaLite_Event* event = nullptr;
    try
    {
        event = new YiaLite_Event();
        event->cpp_event = new yialite::Event();
    }
    catch(const yialite::YiaLite_Exception& e)
    {
        yialite::Logger::error("{}", e.what());
        delete event;
        return NULL;
    }
    catch(const std::exception& e)
    {
        yialite::Logger::error("Failed to create event: {}", e.what());
        delete event;
        return NULL;
    }
    
    return event;
}

void YiaLite_DestroyEvent(YiaLite_Event* event)
{
    if(event) delete event->cpp_event;
    delete event;
}

void YiaLite_EventOnUpdate(YiaLite_Event* event)
{
    event->cpp_event->onUpdate();
}

void YiaLite_SetEventCallbackGlobalData(YiaLite_Event* event, void* data)
{
    event->cpp_event->setGlobalData(data);
}

void YiaLite_RegisterQuitEventCallback(YiaLite_Event* event, YiaLite_QuitEventCallback callback)
{
    event->cpp_event->registerQuitEventCallback(callback);
}

void YiaLite_RegisterKeyEventCallback(YiaLite_Event* event, YiaLite_KeyEventCallback callback)
{
    event->cpp_event->registerKeyEventCallback(callback);
}

void YiaLite_RegisterMouseButtonEventCallback(YiaLite_Event* event, YiaLite_MouseButtonEventCallback callback)
{
    event->cpp_event->registerMouseButtonEventCallback(callback);
}

void YiaLite_RegisterMouseWheelEventCallback(YiaLite_Event* event, YiaLite_MouseWheelEventCallback callback)
{
    event->cpp_event->registerMouseWheelEventCallback(callback);
}

void YiaLite_RegisterMouseMotionEventCallback(YiaLite_Event* event, YiaLite_MouseMotionEventCallback callback)
{
    event->cpp_event->registerMouseMotionEventCallback(callback);
}

void YiaLite_RegisterWindowResizedEventCallback(YiaLite_Event* event, YiaLite_WindowResizedEventCallback callback)
{
    event->cpp_event->registerWindowResizedEventCallback(callback);
}

void YiaLite_RegisterWindowMovedEventCallback(YiaLite_Event* event, YiaLite_WindowMovedEventCallback callback)
{
    event->cpp_event->registerWindowMovedEventCallback(callback);
}

void YiaLite_RegisterWindowFocusGainedEventCallback(YiaLite_Event* event, YiaLite_WindowFocusGainedEventCallback callback)
{
    event->cpp_event->registerWindowFocusGainedEventCallback(callback);
}

void YiaLite_RegisterWindowFocusLostEventCallback(YiaLite_Event* event, YiaLite_WindowFocusLostEventCallback callback)
{
    event->cpp_event->registerWindowFocusLostEventCallback(callback);
}

//input
bool YiaLite_isKeyPressed(YiaLite_Scancode key)
{
    return yialite::isKeyPressed((yialite::Scancode)key);
}

bool YiaLite_isMouseButtonPressed(YiaLite_MouseButtonFlags button, float* x, float* y)
{
    return yialite::isMouseButtonPressed((yialite::MouseButtonFlags)button, x, y);
}

//log
static yialite::LogLevel ToYiaLiteLogLevel(YiaLite_LogLevel level)
{
    if(level == YiaLite_Log_Trace) return yialite::LogLevel::Trace;
    else if(level == YiaLite_Log_Info) return yialite::LogLevel::Info;
    else if(level == YiaLite_Log_Warn) return yialite::LogLevel::Warn;
    else if(level == YiaLite_Log_Err) return yialite::LogLevel::Err;
    else if(level == YiaLite_Log_Fatal) return yialite::LogLevel::Fatal;
    else return yialite::LogLevel::Trace;
}

void YiaLite_SetLogLevel(YiaLite_LogLevel level)
{
    yialite::setLogLevel(ToYiaLiteLogLevel(level));
}

void YiaLite_SetLoggerEnabled(bool enabled)
{
    yialite::setLoggerEnabled(enabled);
}

//initialize
bool YiaLite_Init()
{
    return yialite::init();
}

void YiaLite_Quit()
{
    yialite::quit();
}

//context
YiaLite_Context* YiaLite_InitContext(const YiaLite_WindowConfig* config)
{
    if(!yialite::init()) return NULL;

    YiaLite_Context* context = nullptr;
    try
    {
        context = new YiaLite_Context();
    }
    catch(const std::exception& e)
    {
        yialite::Logger::error("Failed to init context: {}", e.what());
        return NULL;
    }

    if(context->window = YiaLite_CreateWindow(config); !context->window)
    {
        delete context;
        return NULL;
    }

    if(context->renderer = YiaLite_CreateRenderer(context->window); !context->renderer)
    {
        YiaLite_DestroyWindow(context->window);
        delete context;
        return NULL;
    }

    return context;
}

void YiaLite_QuitContext(YiaLite_Context* context)
{
    YiaLite_DestroyRenderer(context->renderer);
    YiaLite_DestroyWindow(context->window);
    delete context;

    yialite::quit();
}

//audio
struct YiaLite_AudioManager
{
    yialite::AudioManager* cpp_audio_manager = nullptr;
};

YiaLite_AudioManager* YiaLite_CreateAudioManager()
{
    YiaLite_AudioManager* audio_manager = nullptr;
    try
    {
        audio_manager = new YiaLite_AudioManager();
        audio_manager->cpp_audio_manager = new yialite::AudioManager();
    }
    catch(const yialite::YiaLite_Exception& e)
    {
        yialite::Logger::error("{}", e.what());
        delete audio_manager;
        return NULL;
    }
    catch(const std::exception& e)
    {
        yialite::Logger::error("Failed to create audio manager: {}", e.what());
        delete audio_manager;
        return NULL;
    }

    return audio_manager;
}

void YiaLite_DestroyAudioManager(YiaLite_AudioManager* audio_manager)
{
    if(audio_manager) delete audio_manager->cpp_audio_manager;
    delete audio_manager;
}

bool YiaLite_AddSound(YiaLite_AudioManager* audio_manager, const char* name, const char* path)
{
    return audio_manager->cpp_audio_manager->addSound(name, path);
}

bool YiaLite_ReplaceSound(YiaLite_AudioManager* audio_manager, const char* name, const char* path)
{
    return audio_manager->cpp_audio_manager->replaceSound(name, path);
}

bool YiaLite_HasSound(YiaLite_AudioManager* audio_manager, const char* name)
{
    return audio_manager->cpp_audio_manager->hasSound(name);
}

void YiaLite_RemoveSound(YiaLite_AudioManager* audio_manager, const char* name)
{
    audio_manager->cpp_audio_manager->removeSound(name);
}

void YiaLite_RemoveAllSounds(YiaLite_AudioManager* audio_manager)
{
    audio_manager->cpp_audio_manager->removeAllSounds();
}

bool YiaLite_PlaySound(YiaLite_AudioManager* audio_manager, const char* path)
{
    return audio_manager->cpp_audio_manager->playSound(path);
}

bool YiaLite_PlaySoundFromName(YiaLite_AudioManager* audio_manager, const char* name, bool loop, float volume)
{
    return audio_manager->cpp_audio_manager->playSoundFromName(name, loop, volume);
}

size_t YiaLite_GetSoundCount(YiaLite_AudioManager* audio_manager)
{
    return audio_manager->cpp_audio_manager->getSoundCount();
}