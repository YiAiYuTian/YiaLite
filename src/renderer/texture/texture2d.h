#ifndef YIALITE_TEXTURE2D_H
#define YIALITE_TEXTURE2D_H

#include "../../core/core.h"
#include "../../core/result.h"

namespace yialite
{

class Renderer2D;

class YIALITE_API Texture2D
{
    FRIEND_ALLOCATOR
    friend class Renderer2D;
public:
    ~Texture2D();
    Texture2D(const Texture2D&) = delete;
    Texture2D& operator=(const Texture2D&) = delete;
    Texture2D(Texture2D&& other) noexcept;
    Texture2D& operator=(Texture2D&& other) noexcept;

    static Result<Texture2D*> create(const char* path, Renderer2D* renderer);
    static Result<Texture2D*> create(int width, int height, Renderer2D* renderer, bool is_target = false);
    static void destroy(Texture2D* texture);

    int get_width() const;
    int get_height() const;

    //For internal use only
    void* get_native_handle();
    const void* get_native_handle() const;

    explicit operator bool() const noexcept { return m_impl != nullptr; }
private:
    Texture2D() = default;
    struct Impl;
    Impl* m_impl = nullptr;
};

}

#endif
