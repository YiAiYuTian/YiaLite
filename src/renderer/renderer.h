#ifndef YIALITE_RENDERER_H
#define YIALITE_RENDERER_H

#include "../core/core.h"
#include "../math/math.h"

namespace yialite
{

constexpr Color default_color = { 255, 255, 255, 255 };
constexpr FColor default_fcolor = { 1.0f, 1.0f, 1.0f, 1.0f };

class Window;

class YIALITE_API Renderer
{
public:
    Renderer(Window* window);
    ~Renderer();

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&&) = delete;

    void beginDraw(Color background_color = { 0, 0, 0, 255 });
    void beginDrawF(FColor background_color = { 0.0f, 0.0f, 0.0f, 1.0f });
    void endDraw();

    //tools
    void drawPoint(const Vector2f& pos, Color color = default_color);
    void drawPoints(const Vector2f* pos, int count, Color color = default_color);
    void drawLine(const Vector2f& start, const Vector2f& end, Color color = default_color);
    void drawRect(const Vector2f& pos, const Vector2f& size, Color color = default_color);
    void drawRect(const FRect& rect, Color color = default_color);
    void drawFillRect(const Vector2f& pos, const Vector2f& size, Color color = default_color);
    void drawFillRect(const FRect& rect, Color color = default_color);
    
    void drawPointF(const Vector2f& pos, FColor color = default_fcolor);
    void drawPointsF(const Vector2f* pos, int count, FColor color = default_fcolor);
    void drawLineF(const Vector2f& start, const Vector2f& end, FColor color = default_fcolor);
    void drawRectF(const Vector2f& pos, const Vector2f& size, FColor color = default_fcolor);
    void drawRectF(const FRect& rect, FColor color = default_fcolor);
    void drawFillRectF(const Vector2f& pos, const Vector2f& size, FColor color = default_fcolor);
    void drawFillRectF(const FRect& rect, FColor color = default_fcolor);
private:
    struct Impl;
    Impl* m_impl = nullptr;
};

}

#endif