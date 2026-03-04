#ifndef RENDERER_H
#define RENDERER_H

#include "../core/core.h"
#include "../math/math.h"

namespace lite
{

class Window;

class LITE_API Renderer
{
public:
    Renderer(Window* window);
    ~Renderer();

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&&) = delete;

    void beginDraw(Color background_color = { 0, 0, 0, 255 });
    void endDraw();

    //tools
    void drawPoint(const Vector2f& pos, Color color = { 255, 255, 255, 255 });
    void drawPoints(const Vector2f* pos, int count, Color color = { 255, 255, 255, 255 });
    void drawLine(const Vector2f& start, const Vector2f& end, Color color = { 255, 255, 255, 255 });
    void drawRect(const Vector2f& pos, const Vector2f& size, Color color = { 255, 255, 255, 255 });
    void drawRect(const FRect& rect, Color color = { 255, 255, 255, 255 });
    void drawFillRect(const Vector2f& pos, const Vector2f& size, Color color = { 255, 255, 255, 255 });
    void drawFillRect(const FRect& rect, Color color = { 255, 255, 255, 255 });
    
    void fdrawPoint(const Vector2f& pos, FColor color = { 1.0f, 1.0f, 1.0f, 1.0f });
    void fdrawPoints(const Vector2f* pos, int count, FColor color = { 1.0f, 1.0f, 1.0f, 1.0f });
    void fdrawLine(const Vector2f& start, const Vector2f& end, FColor color = { 1.0f, 1.0f, 1.0f, 1.0f });
    void fdrawRect(const Vector2f& pos, const Vector2f& size, FColor color = { 1.0f, 1.0f, 1.0f, 1.0f });
    void fdrawRect(const FRect& rect, FColor color = { 1.0f, 1.0f, 1.0f, 1.0f });
    void fdrawFillRect(const Vector2f& pos, const Vector2f& size, FColor color = { 1.0f, 1.0f, 1.0f, 1.0f });
    void fdrawFillRect(const FRect& rect, FColor color = { 1.0f, 1.0f, 1.0f, 1.0f });
private:
    struct Impl;
    Impl* m_impl = nullptr;
};

}

#endif