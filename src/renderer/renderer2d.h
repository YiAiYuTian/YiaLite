#ifndef YIALITE_RENDERER2D_H
#define YIALITE_RENDERER2D_H

#include "render_color.h"
#include "../core/core.h"

namespace yialite
{

class Window;
class Texture2D;

class YIALITE_API Renderer2D
{
public:
    Renderer2D(Window* window);
    ~Renderer2D();

    Renderer2D(const Renderer2D&) = delete;
    Renderer2D& operator=(const Renderer2D&) = delete;
    Renderer2D(Renderer2D&&) = delete;
    Renderer2D& operator=(Renderer2D&&) = delete;

    void beginDraw(const Color& background_color = COLOR_BLACK);
    void beginDrawF(const FColor& background_color = FCOLOR_BLACK);
    void renderClear(const Color& background_color = COLOR_BLACK);
    void renderClearF(const FColor& background_color = FCOLOR_BLACK);
    void endDraw();

    //tools
    void drawPoint(const Vector2f& pos, const Color& color = COLOR_DEFAULT);
    void drawPoints(const Vector2f* pos, int count, const Color& color = COLOR_DEFAULT);
    void drawLine(const Vector2f& start, const Vector2f& end, const Color& color = COLOR_DEFAULT);
    void drawRect(const Vector2f& pos, const Vector2f& size, const Color& color = COLOR_DEFAULT);
    void drawRect(const FRect& rect, const Color& color = COLOR_DEFAULT);
    void drawFillRect(const Vector2f& pos, const Vector2f& size, const Color& color = COLOR_DEFAULT);
    void drawFillRect(const FRect& rect, const Color& color = COLOR_DEFAULT);
    void drawTexture(Texture2D& texture, const FRect* src_rect, const FRect& dst_rect, uint8_t alpha = 255);
    
    void drawPointF(const Vector2f& pos, const FColor& color = FCOLOR_DEFAULT);
    void drawPointsF(const Vector2f* pos, int count, const FColor& color = FCOLOR_DEFAULT);
    void drawLineF(const Vector2f& start, const Vector2f& end, const FColor& color = FCOLOR_DEFAULT);
    void drawRectF(const Vector2f& pos, const Vector2f& size, const FColor& color = FCOLOR_DEFAULT);
    void drawRectF(const FRect& rect, const FColor& color = FCOLOR_DEFAULT);
    void drawFillRectF(const Vector2f& pos, const Vector2f& size, const FColor& color = FCOLOR_DEFAULT);
    void drawFillRectF(const FRect& rect, const FColor& color = FCOLOR_DEFAULT);
    void drawTextureF(Texture2D& texture, const FRect* src_rect, const FRect& dst_rect, float alpha = 1.0f);
    
    void setRenderScale(const Vector2f& size);
    void setRenderTarget(Texture2D* texture = nullptr);

    //For internal use only
    void* getNativeHandle();
    const void* getNativeHandle() const;
private:
    struct Impl;
    Impl* m_impl = nullptr;
};

}

#endif