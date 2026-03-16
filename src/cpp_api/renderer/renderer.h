#ifndef YIALITE_RENDERER_H
#define YIALITE_RENDERER_H

#include "render_color.h"
#include "../core/core.h"

namespace yialite
{

class Window;

class YIALITE_API Renderer
{
    friend class DevUI;
public:
    Renderer(Window* window);
    ~Renderer();

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&&) = delete;

    void beginDraw(Color background_color = COLOR_BLACK);
    void beginDrawF(FColor background_color = FCOLOR_BLACK);
    void endDraw();

    //tools
    void drawPoint(const Vector2f& pos, Color color = COLOR_DEFAULT);
    void drawPoints(const Vector2f* pos, int count, Color color = COLOR_DEFAULT);
    void drawLine(const Vector2f& start, const Vector2f& end, Color color = COLOR_DEFAULT);
    void drawRect(const Vector2f& pos, const Vector2f& size, Color color = COLOR_DEFAULT);
    void drawRect(const FRect& rect, Color color = COLOR_DEFAULT);
    void drawFillRect(const Vector2f& pos, const Vector2f& size, Color color = COLOR_DEFAULT);
    void drawFillRect(const FRect& rect, Color color = COLOR_DEFAULT);
    
    void drawPointF(const Vector2f& pos, FColor color = FCOLOR_DEFAULT);
    void drawPointsF(const Vector2f* pos, int count, FColor color = FCOLOR_DEFAULT);
    void drawLineF(const Vector2f& start, const Vector2f& end, FColor color = FCOLOR_DEFAULT);
    void drawRectF(const Vector2f& pos, const Vector2f& size, FColor color = FCOLOR_DEFAULT);
    void drawRectF(const FRect& rect, FColor color = FCOLOR_DEFAULT);
    void drawFillRectF(const Vector2f& pos, const Vector2f& size, FColor color = FCOLOR_DEFAULT);
    void drawFillRectF(const FRect& rect, FColor color = FCOLOR_DEFAULT);
private:
    struct Impl;
    Impl* m_impl = nullptr;
};

}

#endif