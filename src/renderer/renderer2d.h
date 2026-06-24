#ifndef YIALITE_RENDERER2D_H
#define YIALITE_RENDERER2D_H

#include "render_color.h"
#include "../core/core.h"
#include "../core/result.h"

namespace yialite
{

class IWindow;
class Texture2D;

class YIALITE_API Renderer2D
{
public:
    ~Renderer2D();
    Renderer2D(const Renderer2D&) = delete;
    Renderer2D& operator=(const Renderer2D&) = delete;
    Renderer2D(Renderer2D&& other) noexcept;
    Renderer2D& operator=(Renderer2D&& other) noexcept;

    static Result<Renderer2D*> create(IWindow* window);
    static void destroy(Renderer2D* renderer);

    void begin_draw(const Color& background_color = COLOR_BLACK);
    void begin_draw_f(const FColor& background_color = FCOLOR_BLACK);
    void render_clear(const Color& background_color = COLOR_BLACK);
    void render_clear_f(const FColor& background_color = FCOLOR_BLACK);
    void end_draw();

    //tools
    void draw_point(const Vector2f& pos, const Color& color = COLOR_DEFAULT);
    void draw_points(const Vector2f* pos, int count, const Color& color = COLOR_DEFAULT);
    void draw_line(const Vector2f& start, const Vector2f& end, const Color& color = COLOR_DEFAULT);
    void draw_rect(const Vector2f& pos, const Vector2f& size, const Color& color = COLOR_DEFAULT);
    void draw_rect(const FRect& rect, const Color& color = COLOR_DEFAULT);
    void draw_fill_rect(const Vector2f& pos, const Vector2f& size, const Color& color = COLOR_DEFAULT);
    void draw_fill_rect(const FRect& rect, const Color& color = COLOR_DEFAULT);
    void draw_texture(Texture2D& texture, const FRect* src_rect, const FRect& dst_rect, uint8_t alpha = 255);

    void draw_point_f(const Vector2f& pos, const FColor& color = FCOLOR_DEFAULT);
    void draw_points_f(const Vector2f* pos, int count, const FColor& color = FCOLOR_DEFAULT);
    void draw_line_f(const Vector2f& start, const Vector2f& end, const FColor& color = FCOLOR_DEFAULT);
    void draw_rect_f(const Vector2f& pos, const Vector2f& size, const FColor& color = FCOLOR_DEFAULT);
    void draw_rect_f(const FRect& rect, const FColor& color = FCOLOR_DEFAULT);
    void draw_fill_rect_f(const Vector2f& pos, const Vector2f& size, const FColor& color = FCOLOR_DEFAULT);
    void draw_fill_rect_f(const FRect& rect, const FColor& color = FCOLOR_DEFAULT);
    void draw_texture_f(Texture2D& texture, const FRect* src_rect, const FRect& dst_rect, float alpha = 1.0f);

    void set_render_scale(const Vector2f& size);
    void set_render_target(Texture2D* texture = nullptr);

    //For internal use only
    void* get_native_handle();
    const void* get_native_handle() const;

    explicit operator bool() const noexcept { return m_impl != nullptr; }
private:
    Renderer2D() = default;
    struct Impl;
    Impl* m_impl = nullptr;
};

}

#endif
