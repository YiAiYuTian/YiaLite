#ifndef YIALITE_TEXTURE2D_H
#define YIALITE_TEXTURE2D_H

#include "../../core/core.h"

#include <string_view>

namespace yialite
{

class Renderer2D;

class YIALITE_API Texture2D
{
    friend class Renderer2D;
public:
    Texture2D(std::string_view path, Renderer2D* renderer);
    Texture2D(int width, int height, Renderer2D* renderer, bool is_target = false);
    ~Texture2D();

    int getWidth() const;
    int getHeight() const;

    //For internal use only
    void* getNativeHandle();
    const void* getNativeHandle() const;
private:
    struct Impl;
    Impl* m_impl = nullptr;
};

}

#endif