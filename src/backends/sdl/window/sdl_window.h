#ifndef YIALITE_SDL_WINDOW_H
#define YIALITE_SDL_WINDOW_H

#include "../../../window/window.h"

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_dialog.h>

namespace yialite
{

class SDLWindow : public IWindow
{
public:
    ~SDLWindow() override;

    static Result<IWindow*> create(const WindowConfig& config);
    static void destroy(IWindow* window);

    void show_open_file_dialog(
        DialogFileCallback callback,
        const DialogFileFilter* filters, 
        int nfilters,
        const char* default_location = nullptr, 
        bool allow_many = false
    ) override;
    
    void show_save_file_dialog(
        DialogFileCallback callback, 
        const DialogFileFilter *filters, 
        int nfilters, 
        const char *default_location
    ) override;

    void show_open_folder_dialog(
        DialogFileCallback callback, 
        const char *default_location, 
        bool allow_many
    ) override;

    inline void set_width(int w) override                { int h; SDL_GetWindowSize(m_window, nullptr, &h); SDL_SetWindowSize(m_window, w, h); }
    inline void set_height(int h) override               { int w; SDL_GetWindowSize(m_window, &w, nullptr); SDL_SetWindowSize(m_window, w, h); }
    inline void set_size(int w, int h) override          { SDL_SetWindowSize(m_window, w, h);             }
    inline void set_title(const char* title) override    { SDL_SetWindowTitle(m_window, title);           }
    inline void set_fullscreen(bool fullscreen) override { SDL_SetWindowFullscreen(m_window, fullscreen); }
    
    inline int get_width() const override         { int w; SDL_GetWindowSize(m_window, &w, nullptr); return w;   }
    inline int get_height() const override        { int h; SDL_GetWindowSize(m_window, nullptr, &h); return h;   }
    inline const char* get_title() const override { return SDL_GetWindowTitle(m_window);                         }
    inline WindowID get_id() const override       { return SDL_GetWindowID(m_window);                                   }
    inline bool is_fullscreen() const override    { return SDL_GetWindowFlags(m_window) & SDL_WINDOW_FULLSCREEN; }

    //For internal use only
    inline void* get_native_handle() override { return reinterpret_cast<void*>(m_window); }
    inline const void* get_native_handle() const override { return reinterpret_cast<void*>(m_window); }
private:
    SDLWindow() = default;
private:
    SDL_Window* m_window;
};

}

#endif
