// Matrices and vectors use column-major order.

#ifndef YIALITE_MATH_H
#define YIALITE_MATH_H

#ifdef YIALITE_MATH_STANDALONE
    #include <cassert>
    
    #ifdef _DEBUG
        #define YIALITE_ASSERT(expression) assert(expression)
    #else
        #define YIALITE_ASSERT(expression) ((void)0)
    #endif
#else
    #include "../core/core.h"
#endif

#include <cmath>
#include <limits>

namespace yialite
{

constexpr int TOLERANCE_SCALE = 10;

//================================================================================
//vector2
template<typename T, typename Derived>
struct Vector2Base
{
    [[nodiscard]] constexpr Derived operator-() const noexcept
    {
        auto& self = static_cast<const Derived&>(*this);
        return Derived(-self[0], -self[1]);
    }
    
    [[nodiscard]] constexpr Derived operator+(const Derived &other) const noexcept
    {
        auto& self = static_cast<const Derived&>(*this);

        return Derived(
            self[0] + other[0],
            self[1] + other[1]
        );
    }

    [[nodiscard]] constexpr Derived operator-(const Derived& other) const noexcept
    {
        auto& self = static_cast<const Derived&>(*this);

        return Derived(
            self[0] - other[0],
            self[1] - other[1]
        );
    }

    [[nodiscard]] constexpr Derived operator*(T scalar) const noexcept
    {
        auto& self = static_cast<const Derived&>(*this);

        return Derived(
            self[0] * scalar,
            self[1] * scalar
        );
    }

    [[nodiscard]] constexpr Derived operator/(T scalar) const noexcept
    {
        auto& self = static_cast<const Derived&>(*this);

        if constexpr (std::is_floating_point_v<T>) {
            YIALITE_ASSERT(std::abs(scalar) > std::numeric_limits<T>::epsilon() * TOLERANCE_SCALE && "Vector2 division by zero!");
        } else {
            YIALITE_ASSERT(scalar != 0 && "Vector2 division by zero!");
        }

        T inv = static_cast<T>(1) / scalar;

        return Derived(
            self[0] * inv,
            self[1] * inv
        );
    }

    constexpr Derived& operator+=(const Derived& other) noexcept
    {
        auto& self = static_cast<Derived&>(*this);
        self[0] += other[0];
        self[1] += other[1];

        return self;
    }

    constexpr Derived& operator-=(const Derived& other) noexcept
    {
        auto& self = static_cast<Derived&>(*this);
        self[0] -= other[0];
        self[1] -= other[1];

        return self;
    }

    constexpr Derived& operator*=(T scalar) noexcept
    {
        auto& self = static_cast<Derived&>(*this);
        self[0] *= scalar;
        self[1] *= scalar;

        return self;
    }

    constexpr Derived& operator/=(T scalar) noexcept
    {
        auto& self = static_cast<Derived&>(*this);

        if constexpr (std::is_floating_point_v<T>) {
            YIALITE_ASSERT(std::abs(scalar) > std::numeric_limits<T>::epsilon() * TOLERANCE_SCALE && "Vector2 division by zero!");
        } else {
            YIALITE_ASSERT(scalar != 0 && "Vector2 division by zero!");
        }
        
        T inv = static_cast<T>(1) / scalar;
        self[0] *= inv;
        self[1] *= inv;

        return self;
    }

    constexpr T* begin() noexcept { return &static_cast<Derived&>(*this)[0]; }
    constexpr const T* begin() const noexcept { return &static_cast<const Derived&>(*this)[0]; }
    constexpr T* end() noexcept { return begin() + 2; }
    constexpr const T* end() const noexcept { return begin() + 2; }
};

template <typename T, typename Derived>
[[nodiscard]] constexpr Derived operator*(T scalar, const Vector2Base<T, Derived>& vec) noexcept
{
    return static_cast<const Derived&>(vec) * scalar;
}

struct Vector2f : public Vector2Base<float, Vector2f>
{
    float x, y;

    constexpr Vector2f() : x(0.0f), y(0.0f) {}
    constexpr explicit Vector2f(float v) : x(v), y(v) {}
    constexpr Vector2f(float x_, float y_) : x(x_), y(y_) {}

    constexpr float& operator[](int i) noexcept 
    {
        YIALITE_ASSERT(i >= 0 && i < 2 && "Vector2f index out of bounds!");
        return (&x)[i];
    }
    constexpr const float& operator[](int i) const noexcept 
    {
        YIALITE_ASSERT(i >= 0 && i < 2 && "Vector2f index out of bounds!");
        return (&x)[i];
    }
};

struct Vector2i : public Vector2Base<int, Vector2i>
{
    int x, y;

    constexpr Vector2i() : x(0), y(0) {}
    constexpr explicit Vector2i(int v) : x(v), y(v) {}
    constexpr Vector2i(int x_, int y_) : x(x_), y(y_) {}

    constexpr int& operator[](int i) noexcept 
    {
        YIALITE_ASSERT(i >= 0 && i < 2 && "Vector2i index out of bounds!");
        return (&x)[i]; 
    }
    constexpr const int& operator[](int i) const noexcept 
    {
        YIALITE_ASSERT(i >= 0 && i < 2 && "Vector2i index out of bounds!");
        return (&x)[i];
    }
};

//================================================================================
//vector3
template<typename T, typename Derived>
struct Vector3Base
{
    [[nodiscard]] constexpr Derived operator-() const noexcept
    {
        auto& self = static_cast<const Derived&>(*this);
        return Derived(-self[0], -self[1], -self[2]);
    }
    
    [[nodiscard]] constexpr Derived operator+(const Derived &other) const noexcept
    {
        auto& self = static_cast<const Derived&>(*this);

        return Derived(
            self[0] + other[0],
            self[1] + other[1],
            self[2] + other[2]
        );
    }

    [[nodiscard]] constexpr Derived operator-(const Derived& other) const noexcept
    {
        auto& self = static_cast<const Derived&>(*this);

        return Derived(
            self[0] - other[0],
            self[1] - other[1],
            self[2] - other[2]
        );
    }

    [[nodiscard]] constexpr Derived operator*(T scalar) const noexcept
    {
        auto& self = static_cast<const Derived&>(*this);

        return Derived(
            self[0] * scalar,
            self[1] * scalar,
            self[2] * scalar
        );
    }

    [[nodiscard]] constexpr Derived operator/(T scalar) const noexcept
    {
        auto& self = static_cast<const Derived&>(*this);

        if constexpr (std::is_floating_point_v<T>) {
            YIALITE_ASSERT(std::abs(scalar) > std::numeric_limits<T>::epsilon() * TOLERANCE_SCALE && "Vector3 division by zero!");
        } else {
            YIALITE_ASSERT(scalar != 0 && "Vector3 division by zero!");
        }

        T inv = static_cast<T>(1) / scalar;

        return Derived(
            self[0] * inv,
            self[1] * inv,
            self[2] * inv
        );
    }

    constexpr Derived& operator+=(const Derived& other) noexcept
    {
        auto& self = static_cast<Derived&>(*this);
        self[0] += other[0];
        self[1] += other[1];
        self[2] += other[2];

        return self;
    }

    constexpr Derived& operator-=(const Derived& other) noexcept
    {
        auto& self = static_cast<Derived&>(*this);
        self[0] -= other[0];
        self[1] -= other[1];
        self[2] -= other[2];

        return self;
    }

    constexpr Derived& operator*=(T scalar) noexcept
    {
        auto& self = static_cast<Derived&>(*this);
        self[0] *= scalar;
        self[1] *= scalar;
        self[2] *= scalar;

        return self;
    }

    constexpr Derived& operator/=(T scalar) noexcept
    {
        auto& self = static_cast<Derived&>(*this);

        if constexpr (std::is_floating_point_v<T>) {
            YIALITE_ASSERT(std::abs(scalar) > std::numeric_limits<T>::epsilon() * TOLERANCE_SCALE && "Vector3 division by zero!");
        } else {
            YIALITE_ASSERT(scalar != 0 && "Vector3 division by zero!");
        }
        
        T inv = static_cast<T>(1) / scalar;
        self[0] *= inv;
        self[1] *= inv;
        self[2] *= inv;

        return self;
    }

    constexpr T* begin() noexcept { return &static_cast<Derived&>(*this)[0]; }
    constexpr const T* begin() const noexcept { return &static_cast<const Derived&>(*this)[0]; }
    constexpr T* end() noexcept { return begin() + 3; }
    constexpr const T* end() const noexcept { return begin() + 3; }
};

template <typename T, typename Derived>
[[nodiscard]] constexpr Derived operator*(T scalar, const Vector3Base<T, Derived>& vec) noexcept
{
    return static_cast<const Derived&>(vec) * scalar;
}

struct alignas(16) Vector3f : public Vector3Base<float, Vector3f>
{
    float x, y, z;

    constexpr Vector3f() : x(0.0f), y(0.0f), z(0.0f) {}
    constexpr explicit Vector3f(float v) : x(v), y(v), z(v) {}
    constexpr Vector3f(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

    constexpr float& operator[](int i) noexcept 
    {
        YIALITE_ASSERT(i >= 0 && i < 3 && "Vector3f index out of bounds!");
        return (&x)[i];
    }
    constexpr const float& operator[](int i) const noexcept 
    {
        YIALITE_ASSERT(i >= 0 && i < 3 && "Vector3f index out of bounds!");
        return (&x)[i];
    }
};

struct alignas(16) Vector3i : public Vector3Base<int, Vector3i>
{
    int x, y, z;

    constexpr Vector3i() : x(0), y(0), z(0) {}
    constexpr explicit Vector3i(int v) : x(v), y(v), z(v) {}
    constexpr Vector3i(int x_, int y_, int z_) : x(x_), y(y_), z(z_) {}

    constexpr int& operator[](int i) noexcept 
    {
        YIALITE_ASSERT(i >= 0 && i < 3 && "Vector3i index out of bounds!");
        return (&x)[i];
    }
    constexpr const int& operator[](int i) const noexcept 
    {
        YIALITE_ASSERT(i >= 0 && i < 3 && "Vector3i index out of bounds!");
        return (&x)[i];
    }
};

//================================================================================
//vector4 tag
struct Vector4Tag {};
struct RectTag {};
struct ColorTag {};

//vector4
template<typename T, typename Derived, typename Tag = Vector4Tag>
struct Vector4Base
{
    [[nodiscard]] constexpr Derived operator-() const noexcept
    requires(std::is_same_v<Tag, Vector4Tag>)
    {
        auto& self = static_cast<const Derived&>(*this);
        return Derived(-self[0], -self[1], -self[2], -self[3]);
    }
    
    [[nodiscard]] constexpr Derived operator+(const Derived &other) const noexcept
    requires(std::is_same_v<Tag, Vector4Tag>)
    {
        auto& self = static_cast<const Derived&>(*this);

        return Derived(
            self[0] + other[0],
            self[1] + other[1],
            self[2] + other[2],
            self[3] + other[3]
        );
    }

    [[nodiscard]] constexpr Derived operator-(const Derived& other) const noexcept
    requires(std::is_same_v<Tag, Vector4Tag>)
    {
        auto& self = static_cast<const Derived&>(*this);

        return Derived(
            self[0] - other[0],
            self[1] - other[1],
            self[2] - other[2],
            self[3] - other[3]
        );
    }

    [[nodiscard]] constexpr Derived operator*(T scalar) const noexcept
    requires(std::is_same_v<Tag, Vector4Tag>)
    {
        auto& self = static_cast<const Derived&>(*this);

        return Derived(
            self[0] * scalar,
            self[1] * scalar,
            self[2] * scalar,
            self[3] * scalar
        );
    }

    [[nodiscard]] constexpr Derived operator/(T scalar) const noexcept
    requires(std::is_same_v<Tag, Vector4Tag>)
    {
        auto& self = static_cast<const Derived&>(*this);

        if constexpr (std::is_floating_point_v<T>) {
            YIALITE_ASSERT(std::abs(scalar) > std::numeric_limits<T>::epsilon() * TOLERANCE_SCALE && "Vector4 division by zero!");
        } else {
            YIALITE_ASSERT(scalar != 0 && "Vector4 division by zero!");
        }

        T inv = static_cast<T>(1) / scalar;

        return Derived(
            self[0] * inv,
            self[1] * inv,
            self[2] * inv,
            self[3] * inv
        );
    }

    constexpr Derived& operator+=(const Derived& other) noexcept
    requires(std::is_same_v<Tag, Vector4Tag>)
    {
        auto& self = static_cast<Derived&>(*this);
        self[0] += other[0];
        self[1] += other[1];
        self[2] += other[2];
        self[3] += other[3];

        return self;
    }

    constexpr Derived& operator-=(const Derived& other) noexcept
    requires(std::is_same_v<Tag, Vector4Tag>)
    {
        auto& self = static_cast<Derived&>(*this);
        self[0] -= other[0];
        self[1] -= other[1];
        self[2] -= other[2];
        self[3] -= other[3];

        return self;
    }

    constexpr Derived& operator*=(T scalar) noexcept
    requires(std::is_same_v<Tag, Vector4Tag>)
    {
        auto& self = static_cast<Derived&>(*this);
        self[0] *= scalar;
        self[1] *= scalar;
        self[2] *= scalar;
        self[3] *= scalar;

        return self;
    }

    constexpr Derived& operator/=(T scalar) noexcept
    requires(std::is_same_v<Tag, Vector4Tag>)
    {
        auto& self = static_cast<Derived&>(*this);

        if constexpr (std::is_floating_point_v<T>) {
            YIALITE_ASSERT(std::abs(scalar) > std::numeric_limits<T>::epsilon() * TOLERANCE_SCALE && "Vector4 division by zero!");
        } else {
            YIALITE_ASSERT(scalar != 0 && "Vector4 division by zero!");
        }
        
        T inv = static_cast<T>(1) / scalar;
        self[0] *= inv;
        self[1] *= inv;
        self[2] *= inv;
        self[3] *= inv;

        return self;
    }

    constexpr T* begin() noexcept { return &static_cast<Derived&>(*this)[0]; }
    constexpr const T* begin() const noexcept { return &static_cast<const Derived&>(*this)[0]; }
    constexpr T* end() noexcept { return begin() + 4; }
    constexpr const T* end() const noexcept { return begin() + 4; }
};

template <typename T, typename Derived, typename Tag = Vector4Tag>
[[nodiscard]] constexpr Derived operator*(T scalar, const Vector4Base<T, Derived, Tag>& vec) noexcept
{
    return static_cast<const Derived&>(vec) * scalar;
}

struct alignas(16) Vector4f : public Vector4Base<float, Vector4f>
{
    float x, y, z, w;

    constexpr Vector4f() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    constexpr explicit Vector4f(float v) : x(v), y(v), z(v), w(v) {}
    constexpr Vector4f(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {}

    constexpr float& operator[](int i) noexcept 
    {
        YIALITE_ASSERT(i >= 0 && i < 4 && "Vector4f index out of bounds!");
        return (&x)[i];
    }
    constexpr const float& operator[](int i) const noexcept 
    {
        YIALITE_ASSERT(i >= 0 && i < 4 && "Vector4f index out of bounds!");
        return (&x)[i];
    }
};

struct alignas(16) Vector4i : public Vector4Base<int, Vector4i>
{
    int x, y, z, w;

    constexpr Vector4i() : x(0), y(0), z(0), w(0) {}
    constexpr explicit Vector4i(int v) : x(v), y(v), z(v), w(v) {}
    constexpr Vector4i(int x_, int y_, int z_, int w_) : x(x_), y(y_), z(z_), w(w_) {}

    constexpr int& operator[](int i) noexcept 
    {
        YIALITE_ASSERT(i >= 0 && i < 4 && "Vector4i index out of bounds!");
        return (&x)[i];
    }
    constexpr const int& operator[](int i) const noexcept 
    {
        YIALITE_ASSERT(i >= 0 && i < 4 && "Vector4i index out of bounds!");
        return (&x)[i];
    }
};

struct alignas(16) Rect : public Vector4Base<int, Rect, RectTag>
{
    int x, y, w, h;

    constexpr Rect() : x(0), y(0), w(0), h(0) {}
    constexpr explicit Rect(int v) : x(v), y(v), w(v), h(v) {}
    constexpr Rect(int x_, int y_, int w_, int h_) : x(x_), y(y_), w(w_), h(h_) {}

    constexpr int& operator[](int i) noexcept 
    {
        YIALITE_ASSERT(i >= 0 && i < 4 && "Rect index out of bounds!");
        return (&x)[i];
    }
    constexpr const int& operator[](int i) const noexcept 
    {
        YIALITE_ASSERT(i >= 0 && i < 4 && "Rect index out of bounds!");
        return (&x)[i];
    }
};

struct alignas(16) FRect : public Vector4Base<float, FRect, RectTag>
{
    float x, y, w, h;

    constexpr FRect() : x(0.0f), y(0.0f), w(0.0f), h(0.0f) {}
    constexpr explicit FRect(float v) : x(v), y(v), w(v), h(v) {}
    constexpr FRect(float x_, float y_, float w_, float h_) : x(x_), y(y_), w(w_), h(h_) {}

    constexpr float& operator[](int i) noexcept 
    {
        YIALITE_ASSERT(i >= 0 && i < 4 && "FRect index out of bounds!");
        return (&x)[i];
    }
    constexpr const float& operator[](int i) const noexcept 
    {
        YIALITE_ASSERT(i >= 0 && i < 4 && "FRect index out of bounds!");
        return (&x)[i];
    }
};

struct Color : public Vector4Base<unsigned char, Color, ColorTag>
{
    unsigned char r, g, b, a;

    constexpr Color() : r(0), g(0), b(0), a(0) {}
    constexpr explicit Color(unsigned char v) : r(v), g(v), b(v), a(v) {}
    constexpr Color(unsigned char r_, unsigned char g_, unsigned char b_, unsigned char a_) : r(r_), g(g_), b(b_), a(a_) {}

    constexpr unsigned char& operator[](int i) noexcept 
    {
        YIALITE_ASSERT(i >= 0 && i < 4 && "Color index out of bounds!");
        return (&r)[i];
    }
    constexpr const unsigned char& operator[](int i) const noexcept 
    {
        YIALITE_ASSERT(i >= 0 && i < 4 && "Color index out of bounds!");
        return (&r)[i];
    }
};

struct alignas(16) FColor : public Vector4Base<float, FColor, ColorTag>
{
    float r, g, b, a;

    constexpr FColor() : r(0.0f), g(0.0f), b(0.0f), a(0.0f) {}
    constexpr explicit FColor(float v) : r(v), g(v), b(v), a(v) {}
    constexpr FColor(float r_, float g_, float b_, float a_) : r(r_), g(g_), b(b_), a(a_) {}

    constexpr float& operator[](int i) noexcept 
    {
        YIALITE_ASSERT(i >= 0 && i < 4 && "FColor index out of bounds!");
        return (&r)[i];
    }
    constexpr const float& operator[](int i) const noexcept 
    {
        YIALITE_ASSERT(i >= 0 && i < 4 && "FColor index out of bounds!");
        return (&r)[i];
    }
};

//================================================================================
//mat3
template<typename T, typename Derived>
struct Matrix3Base
{
    [[nodiscard]] constexpr Derived operator-() const noexcept
    {
        auto& self = static_cast<const Derived&>(*this);
        return Derived(
            -self[0][0], -self[0][1], -self[0][2],
            -self[1][0], -self[1][1], -self[1][2],
            -self[2][0], -self[2][1], -self[2][2]
        );
    }

    [[nodiscard]] constexpr Derived operator+(const Derived &other) const noexcept
    {
        auto& self = static_cast<const Derived&>(*this);

        return Derived(
            self[0][0] + other[0][0], self[0][1] + other[0][1], self[0][2] + other[0][2],
            self[1][0] + other[1][0], self[1][1] + other[1][1], self[1][2] + other[1][2],
            self[2][0] + other[2][0], self[2][1] + other[2][1], self[2][2] + other[2][2]
        );
    }

    [[nodiscard]] constexpr Derived operator-(const Derived& other) const noexcept
    {
        auto& self = static_cast<const Derived&>(*this);

        return Derived(
            self[0][0] - other[0][0], self[0][1] - other[0][1], self[0][2] - other[0][2],
            self[1][0] - other[1][0], self[1][1] - other[1][1], self[1][2] - other[1][2],
            self[2][0] - other[2][0], self[2][1] - other[2][1], self[2][2] - other[2][2]
        );
    }

    [[nodiscard]] constexpr Derived operator*(T scalar) const noexcept
    {
        auto& self = static_cast<const Derived&>(*this);

        return Derived(
            self[0][0] * scalar, self[0][1] * scalar, self[0][2] * scalar,
            self[1][0] * scalar, self[1][1] * scalar, self[1][2] * scalar,
            self[2][0] * scalar, self[2][1] * scalar, self[2][2] * scalar
        );
    }

    constexpr Derived& operator+=(const Derived& other) noexcept
    {
        auto& self = static_cast<Derived&>(*this);
        self[0][0] += other[0][0]; self[0][1] += other[0][1]; self[0][2] += other[0][2];
        self[1][0] += other[1][0]; self[1][1] += other[1][1]; self[1][2] += other[1][2];
        self[2][0] += other[2][0]; self[2][1] += other[2][1]; self[2][2] += other[2][2];

        return self;
    }

    constexpr Derived& operator-=(const Derived& other) noexcept
    {
        auto& self = static_cast<Derived&>(*this);
        self[0][0] -= other[0][0]; self[0][1] -= other[0][1]; self[0][2] -= other[0][2];
        self[1][0] -= other[1][0]; self[1][1] -= other[1][1]; self[1][2] -= other[1][2];
        self[2][0] -= other[2][0]; self[2][1] -= other[2][1]; self[2][2] -= other[2][2];

        return self;
    }

    constexpr Derived& operator*=(T scalar) noexcept
    {
        auto& self = static_cast<Derived&>(*this);
        self[0][0] *= scalar; self[1][0] *= scalar; self[2][0] *= scalar;
        self[0][1] *= scalar; self[1][1] *= scalar; self[2][1] *= scalar;
        self[0][2] *= scalar; self[1][2] *= scalar; self[2][2] *= scalar;

        return self;
    }

    constexpr Derived& operator*=(const Derived& other) noexcept
    {
        auto& self = static_cast<Derived&>(*this);
        self = self * other;

        return self;
    }

    constexpr T* begin() noexcept { return &static_cast<Derived&>(*this)[0][0]; }
    constexpr const T* begin() const noexcept { return &static_cast<const Derived&>(*this)[0][0]; }
    constexpr T* end() noexcept { return begin() + 9; }
    constexpr const T* end() const noexcept { return begin() + 9; }
};

template<typename T, typename Derived>
[[nodiscard]] constexpr Derived operator*(T scalar, const Matrix3Base<T, Derived>& mat3) noexcept
{
    return static_cast<const Derived&>(mat3) * scalar;
}

template<typename T, typename Derived>
[[nodiscard]] constexpr Derived operator*(const Matrix3Base<T, Derived>& lhs, const Matrix3Base<T, Derived>& rhs) noexcept
{
    const auto& a = static_cast<const Derived&>(lhs);
    const auto& b = static_cast<const Derived&>(rhs);

    return Derived(
        a[0][0] * b[0][0] + a[1][0] * b[0][1] + a[2][0] * b[0][2],
        a[0][1] * b[0][0] + a[1][1] * b[0][1] + a[2][1] * b[0][2],
        a[0][2] * b[0][0] + a[1][2] * b[0][1] + a[2][2] * b[0][2],

        a[0][0] * b[1][0] + a[1][0] * b[1][1] + a[2][0] * b[1][2],
        a[0][1] * b[1][0] + a[1][1] * b[1][1] + a[2][1] * b[1][2],
        a[0][2] * b[1][0] + a[1][2] * b[1][1] + a[2][2] * b[1][2],

        a[0][0] * b[2][0] + a[1][0] * b[2][1] + a[2][0] * b[2][2],
        a[0][1] * b[2][0] + a[1][1] * b[2][1] + a[2][1] * b[2][2],
        a[0][2] * b[2][0] + a[1][2] * b[2][1] + a[2][2] * b[2][2]
    );
}

struct alignas(16) Matrix3f : public Matrix3Base<float, Matrix3f>
{
    float data[3][3];

    constexpr Matrix3f() : data{} {}
    constexpr explicit Matrix3f(float v)
    { 
        data[0][0] = data[1][1] = data[2][2] = v;
        data[0][1] = data[0][2] = 0.0f;
        data[1][0] = data[1][2] = 0.0f;
        data[2][0] = data[2][1] = 0.0f;
    }
    constexpr Matrix3f(float m00, float m10, float m20,
                       float m01, float m11, float m21,
                       float m02, float m12, float m22)
    : data{{m00, m10, m20},
           {m01, m11, m21},
           {m02, m12, m22}} {}

    [[nodiscard]] constexpr Vector3f operator*(const Vector3f& other) const noexcept
    {
        return Vector3f(
            data[0][0] * other.x + data[1][0] * other.y + data[2][0] * other.z,
            data[0][1] * other.x + data[1][1] * other.y + data[2][1] * other.z,
            data[0][2] * other.x + data[1][2] * other.y + data[2][2] * other.z
        );
    }

    constexpr float* operator[](int i) noexcept
    {
        YIALITE_ASSERT(i >= 0 && i < 3 && "Matrix3f index out of bounds!");
        return data[i];
    }
    constexpr const float* operator[](int i) const noexcept 
    {
        YIALITE_ASSERT(i >= 0 && i < 3 && "Matrix3f index out of bounds!");
        return data[i];
    }
};

//================================================================================
//mat4
template<typename T, typename Derived>
struct Matrix4Base
{
    [[nodiscard]] constexpr Derived operator-() const noexcept
    {
        auto& self = static_cast<const Derived&>(*this);
        return Derived(
            -self[0][0], -self[0][1], -self[0][2], -self[0][3],
            -self[1][0], -self[1][1], -self[1][2], -self[1][3],
            -self[2][0], -self[2][1], -self[2][2], -self[2][3],
            -self[3][0], -self[3][1], -self[3][2], -self[3][3]
        );
    }

    [[nodiscard]] constexpr Derived operator+(const Derived &other) const noexcept
    {
        auto& self = static_cast<const Derived&>(*this);

        return Derived(
            self[0][0] + other[0][0], self[0][1] + other[0][1], self[0][2] + other[0][2], self[0][3] + other[0][3],
            self[1][0] + other[1][0], self[1][1] + other[1][1], self[1][2] + other[1][2], self[1][3] + other[1][3],
            self[2][0] + other[2][0], self[2][1] + other[2][1], self[2][2] + other[2][2], self[2][3] + other[2][3],
            self[3][0] + other[3][0], self[3][1] + other[3][1], self[3][2] + other[3][2], self[3][3] + other[3][3]
        ); 
     }

    [[nodiscard]] constexpr Derived operator-(const Derived& other) const noexcept
    {
        auto& self = static_cast<const Derived&>(*this);

          return Derived(
            self[0][0] - other[0][0], self[0][1] - other[0][1], self[0][2] - other[0][2], self[0][3] - other[0][3],
            self[1][0] - other[1][0], self[1][1] - other[1][1], self[1][2] - other[1][2], self[1][3] - other[1][3],
            self[2][0] - other[2][0], self[2][1] - other[2][1], self[2][2] - other[2][2], self[2][3] - other[2][3],
            self[3][0] - other[3][0], self[3][1] - other[3][1], self[3][2] - other[3][2], self[3][3] - other[3][3]
        );
    }

    [[nodiscard]] constexpr Derived operator*(T scalar) const noexcept
    {
        auto& self = static_cast<const Derived&>(*this);

        return Derived(
            self[0][0] * scalar, self[0][1] * scalar, self[0][2] * scalar, self[0][3] * scalar,
            self[1][0] * scalar, self[1][1] * scalar, self[1][2] * scalar, self[1][3] * scalar,
            self[2][0] * scalar, self[2][1] * scalar, self[2][2] * scalar, self[2][3] * scalar,
            self[3][0] * scalar, self[3][1] * scalar, self[3][2] * scalar, self[3][3] * scalar
        );
    }

    constexpr Derived& operator+=(const Derived& other) noexcept
    {
        auto& self = static_cast<Derived&>(*this);
        self[0][0] += other[0][0]; self[1][0] += other[1][0]; self[2][0] += other[2][0]; self[3][0] += other[3][0];
        self[0][1] += other[0][1]; self[1][1] += other[1][1]; self[2][1] += other[2][1]; self[3][1] += other[3][1];
        self[0][2] += other[0][2]; self[1][2] += other[1][2]; self[2][2] += other[2][2]; self[3][2] += other[3][2];
        self[0][3] += other[0][3]; self[1][3] += other[1][3]; self[2][3] += other[2][3]; self[3][3] += other[3][3];

        return self;
    }

    constexpr Derived& operator-=(const Derived& other) noexcept
    {
        auto& self = static_cast<Derived&>(*this);
        self[0][0] -= other[0][0]; self[1][0] -= other[1][0]; self[2][0] -= other[2][0]; self[3][0] -= other[3][0];
        self[0][1] -= other[0][1]; self[1][1] -= other[1][1]; self[2][1] -= other[2][1]; self[3][1] -= other[3][1];
        self[0][2] -= other[0][2]; self[1][2] -= other[1][2]; self[2][2] -= other[2][2]; self[3][2] -= other[3][2];
        self[0][3] -= other[0][3]; self[1][3] -= other[1][3]; self[2][3] -= other[2][3]; self[3][3] -= other[3][3];

        return self;
    }

    constexpr Derived& operator*=(T scalar) noexcept
    {
        auto& self = static_cast<Derived&>(*this);
        self[0][0] *= scalar; self[1][0] *= scalar; self[2][0] *= scalar; self[3][0] *= scalar;
        self[0][1] *= scalar; self[1][1] *= scalar; self[2][1] *= scalar; self[3][1] *= scalar;
        self[0][2] *= scalar; self[1][2] *= scalar; self[2][2] *= scalar; self[3][2] *= scalar;
        self[0][3] *= scalar; self[1][3] *= scalar; self[2][3] *= scalar; self[3][3] *= scalar;

        return self;
    }

    constexpr Derived& operator*=(const Derived& other) noexcept
    {
        auto& self = static_cast<Derived&>(*this);
        self = self * other;

        return self;
    }

    constexpr T* begin() noexcept { return &static_cast<Derived&>(*this)[0][0]; }
    constexpr const T* begin() const noexcept { return &static_cast<const Derived&>(*this)[0][0]; }
    constexpr T* end() noexcept { return begin() + 16; }
    constexpr const T* end() const noexcept { return begin() + 16; }
};

template<typename T, typename Derived>
[[nodiscard]] constexpr Derived operator*(T scalar, const Matrix4Base<T, Derived>& mat4) noexcept
{
    return static_cast<const Derived&>(mat4) * scalar;
}

template<typename T, typename Derived>
[[nodiscard]] constexpr Derived operator*(const Matrix4Base<T, Derived>& lhs, const Matrix4Base<T, Derived>& rhs) noexcept
{
    const auto& a = static_cast<const Derived&>(lhs);
    const auto& b = static_cast<const Derived&>(rhs);

    return Derived(
        a[0][0] * b[0][0] + a[1][0] * b[0][1] + a[2][0] * b[0][2] + a[3][0] * b[0][3],
        a[0][1] * b[0][0] + a[1][1] * b[0][1] + a[2][1] * b[0][2] + a[3][1] * b[0][3],
        a[0][2] * b[0][0] + a[1][2] * b[0][1] + a[2][2] * b[0][2] + a[3][2] * b[0][3],
        a[0][3] * b[0][0] + a[1][3] * b[0][1] + a[2][3] * b[0][2] + a[3][3] * b[0][3],

        a[0][0] * b[1][0] + a[1][0] * b[1][1] + a[2][0] * b[1][2] + a[3][0] * b[1][3],
        a[0][1] * b[1][0] + a[1][1] * b[1][1] + a[2][1] * b[1][2] + a[3][1] * b[1][3],
        a[0][2] * b[1][0] + a[1][2] * b[1][1] + a[2][2] * b[1][2] + a[3][2] * b[1][3],
        a[0][3] * b[1][0] + a[1][3] * b[1][1] + a[2][3] * b[1][2] + a[3][3] * b[1][3],

        a[0][0] * b[2][0] + a[1][0] * b[2][1] + a[2][0] * b[2][2] + a[3][0] * b[2][3],
        a[0][1] * b[2][0] + a[1][1] * b[2][1] + a[2][1] * b[2][2] + a[3][1] * b[2][3],
        a[0][2] * b[2][0] + a[1][2] * b[2][1] + a[2][2] * b[2][2] + a[3][2] * b[2][3],
        a[0][3] * b[2][0] + a[1][3] * b[2][1] + a[2][3] * b[2][2] + a[3][3] * b[2][3],

        a[0][0] * b[3][0] + a[1][0] * b[3][1] + a[2][0] * b[3][2] + a[3][0] * b[3][3],
        a[0][1] * b[3][0] + a[1][1] * b[3][1] + a[2][1] * b[3][2] + a[3][1] * b[3][3],
        a[0][2] * b[3][0] + a[1][2] * b[3][1] + a[2][2] * b[3][2] + a[3][2] * b[3][3],
        a[0][3] * b[3][0] + a[1][3] * b[3][1] + a[2][3] * b[3][2] + a[3][3] * b[3][3]
    );
}

struct alignas(16) Matrix4f : public Matrix4Base<float, Matrix4f>
{
    float data[4][4];

    constexpr Matrix4f() : data{} {}
    constexpr explicit Matrix4f(float v)
    { 
        data[0][0] = data[1][1] = data[2][2] = data[3][3] = v;
        data[0][1] = data[0][2] = data[0][3] = 0.0f;
        data[1][0] = data[1][2] = data[1][3] = 0.0f;
        data[2][0] = data[2][1] = data[2][3] = 0.0f;
        data[3][0] = data[3][1] = data[3][2] = 0.0f;
    }
    constexpr Matrix4f(float m00, float m10, float m20, float m30,
                       float m01, float m11, float m21, float m31,
                       float m02, float m12, float m22, float m32,
                       float m03, float m13, float m23, float m33)
    : data{{m00, m10, m20, m30},
           {m01, m11, m21, m31},
           {m02, m12, m22, m32},
           {m03, m13, m23, m33}} {}

    [[nodiscard]] constexpr Vector4f operator*(const Vector4f& other) const noexcept
    {
        return Vector4f(
            data[0][0] * other.x + data[1][0] * other.y + data[2][0] * other.z + data[3][0] * other.w,
            data[0][1] * other.x + data[1][1] * other.y + data[2][1] * other.z + data[3][1] * other.w,
            data[0][2] * other.x + data[1][2] * other.y + data[2][2] * other.z + data[3][2] * other.w,
            data[0][3] * other.x + data[1][3] * other.y + data[2][3] * other.z + data[3][3] * other.w
        );
    }

    constexpr float* operator[](int i) noexcept
    {
        YIALITE_ASSERT(i >= 0 && i < 4 && "Matrix4f index out of bounds!");
        return data[i];
    }
    constexpr const float* operator[](int i) const noexcept 
    {
        YIALITE_ASSERT(i >= 0 && i < 4 && "Matrix4f index out of bounds!");
        return data[i];
    }
};

static_assert(std::is_standard_layout_v<Vector2f>, "must be C layout");
static_assert(std::is_standard_layout_v<Vector2i>, "must be C layout");
static_assert(std::is_standard_layout_v<Vector3f>, "must be C layout");
static_assert(std::is_standard_layout_v<Vector3i>, "must be C layout");
static_assert(std::is_standard_layout_v<Vector4f>, "must be C layout");
static_assert(std::is_standard_layout_v<Vector4i>, "must be C layout");
static_assert(std::is_standard_layout_v<Rect>,     "must be C layout");
static_assert(std::is_standard_layout_v<FRect>,    "must be C layout");
static_assert(std::is_standard_layout_v<Color>,    "must be C layout");
static_assert(std::is_standard_layout_v<FColor>,   "must be C layout");
static_assert(std::is_standard_layout_v<Matrix3f>, "must be C layout");
static_assert(std::is_standard_layout_v<Matrix4f>, "must be C layout");

//================================================================================
//tools

//vector
[[nodiscard]] constexpr inline float lengthSquared(const Vector2f& v) noexcept
{
    return v.x * v.x + v.y * v.y;
}

[[nodiscard]] constexpr inline float lengthSquared(const Vector3f& v) noexcept
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

[[nodiscard]] constexpr inline float lengthSquared(const Vector4f& v) noexcept
{
    return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
}

[[nodiscard]] constexpr inline float dot(const Vector2f& a, const Vector2f& b) noexcept
{
    return a.x * b.x + a.y * b.y;
}

[[nodiscard]] constexpr inline float dot(const Vector3f& a, const Vector3f& b) noexcept
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

[[nodiscard]] constexpr inline float dot(const Vector4f& a, const Vector4f& b) noexcept
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

[[nodiscard]] constexpr inline float cross(const Vector2f& a, const Vector2f& b) noexcept
{
    return a.x * b.y - a.y * b.x;
}

[[nodiscard]] constexpr inline Vector3f cross(const Vector3f& a, const Vector3f& b) noexcept
{
    return Vector3f(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

template <typename T>
[[nodiscard]] constexpr float length(const T& v) noexcept
{
    return std::sqrt(lengthSquared(v));
}

template <typename T>
[[nodiscard]] constexpr T normalize(const T& v) noexcept
{
    float len = length(v);
    if (len < std::numeric_limits<float>::epsilon() * TOLERANCE_SCALE) return T();
    return v / len;
}

template<typename T>
[[nodiscard]] constexpr float distanceSquared(const T& a, const T& b) noexcept
{
    return lengthSquared(b - a);
}

template<typename T>
[[nodiscard]] constexpr float distance(const T& a, const T& b) noexcept
{
    return length(b - a);
}

//matrix
[[nodiscard]] constexpr inline Matrix3f transpose(const Matrix3f& m) noexcept
{
    return Matrix3f(
        m[0][0], m[1][0], m[2][0],
        m[0][1], m[1][1], m[2][1],
        m[0][2], m[1][2], m[2][2]
    );
}

[[nodiscard]] inline Matrix3f inverse(const Matrix3f& m) noexcept
{
    float det0 = m[1][1] * m[2][2] - m[1][2] * m[2][1];
    float det1 = m[1][0] * m[2][2] - m[1][2] * m[2][0];
    float det2 = m[1][0] * m[2][1] - m[1][1] * m[2][0];

    float det = m[0][0] * det0 - m[0][1] * det1 + m[0][2] * det2;
    if(std::abs(det) < std::numeric_limits<float>::epsilon() * TOLERANCE_SCALE) 
    {
        return Matrix3f(
            NAN, NAN, NAN,
            NAN, NAN, NAN,
            NAN, NAN, NAN
        );
    }

    float inv_det = 1.0f / det;

    return Matrix3f(
         det0 * inv_det,
        -det1 * inv_det,
         det2 * inv_det,

        (-m[0][1] * m[2][2] + m[0][2] * m[2][1]) * inv_det,
        ( m[0][0] * m[2][2] - m[0][2] * m[2][0]) * inv_det,
        (-m[0][0] * m[2][1] + m[0][1] * m[2][0]) * inv_det,

        ( m[0][1] * m[1][2] - m[0][2] * m[1][1]) * inv_det,
        (-m[0][0] * m[1][2] + m[0][2] * m[1][0]) * inv_det,
        ( m[0][0] * m[1][1] - m[0][1] * m[1][0]) * inv_det
    );
}

[[nodiscard]] constexpr inline Matrix4f transpose(const Matrix4f& m) noexcept
{
    return Matrix4f(
        m[0][0], m[1][0], m[2][0], m[3][0],
        m[0][1], m[1][1], m[2][1], m[3][1],
        m[0][2], m[1][2], m[2][2], m[3][2],
        m[0][3], m[1][3], m[2][3], m[3][3]
    );
}

[[nodiscard]] inline Matrix4f inverse(const Matrix4f& m) noexcept
{
    const float m00 = m[0][0], m01 = m[0][1], m02 = m[0][2], m03 = m[0][3];
    const float m10 = m[1][0], m11 = m[1][1], m12 = m[1][2], m13 = m[1][3];
    const float m20 = m[2][0], m21 = m[2][1], m22 = m[2][2], m23 = m[2][3];
    const float m30 = m[3][0], m31 = m[3][1], m32 = m[3][2], m33 = m[3][3];

    const float s0 = m00 * m11 - m10 * m01;
    const float s1 = m00 * m12 - m10 * m02;
    const float s2 = m00 * m13 - m10 * m03;
    const float s3 = m01 * m12 - m11 * m02;
    const float s4 = m01 * m13 - m11 * m03;
    const float s5 = m02 * m13 - m12 * m03;
    
    const float c5 = m22 * m33 - m32 * m23;
    const float c4 = m21 * m33 - m31 * m23;
    const float c3 = m21 * m32 - m31 * m22;
    const float c2 = m20 * m33 - m30 * m23;
    const float c1 = m20 * m32 - m30 * m22;
    const float c0 = m20 * m31 - m30 * m21;

    const float det = s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0;
    
    if (std::abs(det) < std::numeric_limits<float>::epsilon() * 100.0f)
    {
        return Matrix4f{
            NAN, NAN, NAN, NAN,
            NAN, NAN, NAN, NAN,
            NAN, NAN, NAN, NAN,
            NAN, NAN, NAN, NAN
        };
    }

    const float invDet = 1.0f / det;

    const float t00 = (m11 * c5 - m12 * c4 + m13 * c3) * invDet;
    const float t10 = (-m10 * c5 + m12 * c2 - m13 * c1) * invDet;
    const float t20 = (m10 * c4 - m11 * c2 + m13 * c0) * invDet;
    const float t30 = (-m10 * c3 + m11 * c1 - m12 * c0) * invDet;
    
    const float t01 = (-m01 * c5 + m02 * c4 - m03 * c3) * invDet;
    const float t11 = (m00 * c5 - m02 * c2 + m03 * c1) * invDet;
    const float t21 = (-m00 * c4 + m01 * c2 - m03 * c0) * invDet;
    const float t31 = (m00 * c3 - m01 * c1 + m02 * c0) * invDet;
    
    const float t02 = (m31 * s5 - m32 * s4 + m33 * s3) * invDet;
    const float t12 = (-m30 * s5 + m32 * s2 - m33 * s1) * invDet;
    const float t22 = (m30 * s4 - m31 * s2 + m33 * s0) * invDet;
    const float t32 = (-m30 * s3 + m31 * s1 - m32 * s0) * invDet;
    
    const float t03 = (-m21 * s5 + m22 * s4 - m23 * s3) * invDet;
    const float t13 = (m20 * s5 - m22 * s2 + m23 * s1) * invDet;
    const float t23 = (-m20 * s4 + m21 * s2 - m23 * s0) * invDet;
    const float t33 = (m20 * s3 - m21 * s1 + m22 * s0) * invDet;

    return Matrix4f{
        t00, t01, t02, t03,
        t10, t11, t12, t13,
        t20, t21, t22, t23,
        t30, t31, t32, t33
    };
}

[[nodiscard]] constexpr inline Matrix4f translate(const Matrix4f& m, const Vector3f& v) noexcept
{
    Matrix4f t(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        v.x,  v.y,  v.z,  1.0f
    );

    return m * t;
}

[[nodiscard]] inline Matrix4f rotate(const Matrix4f& m, float angle, const Vector3f& v) noexcept
{
    float a = angle;
    float c = std::cos(a);
    float s = std::sin(a);

    Vector3f axis = normalize(v);
    Vector3f temp((1.0f - c) * axis);

    Matrix4f rot;
    rot[0][0] = c + temp.x * axis.x;
    rot[0][1] = temp.x * axis.y + s * axis.z;
    rot[0][2] = temp.x * axis.z - s * axis.y;
    rot[0][3] = 0.0f;

    rot[1][0] = temp.y * axis.x - s * axis.z;
    rot[1][1] = c + temp.y * axis.y;
    rot[1][2] = temp.y * axis.z + s * axis.x;
    rot[1][3] = 0.0f;

    rot[2][0] = temp.z * axis.x + s * axis.y;
    rot[2][1] = temp.z * axis.y - s * axis.x;
    rot[2][2] = c + temp.z * axis.z;
    rot[2][3] = 0.0f;

    rot[3][0] = 0.0f;
    rot[3][1] = 0.0f;
    rot[3][2] = 0.0f;
    rot[3][3] = 1.0f;

    Matrix4f res;

    res[0][0] = m[0][0] * rot[0][0] + m[1][0] * rot[0][1] + m[2][0] * rot[0][2];
    res[1][0] = m[0][0] * rot[1][0] + m[1][0] * rot[1][1] + m[2][0] * rot[1][2];
    res[2][0] = m[0][0] * rot[2][0] + m[1][0] * rot[2][1] + m[2][0] * rot[2][2];
    res[3][0] = m[3][0];

    res[0][1] = m[0][1] * rot[0][0] + m[1][1] * rot[0][1] + m[2][1] * rot[0][2];
    res[1][1] = m[0][1] * rot[1][0] + m[1][1] * rot[1][1] + m[2][1] * rot[1][2];
    res[2][1] = m[0][1] * rot[2][0] + m[1][1] * rot[2][1] + m[2][1] * rot[2][2];
    res[3][1] = m[3][1];

    res[0][2] = m[0][2] * rot[0][0] + m[1][2] * rot[0][1] + m[2][2] * rot[0][2];
    res[1][2] = m[0][2] * rot[1][0] + m[1][2] * rot[1][1] + m[2][2] * rot[1][2];
    res[2][2] = m[0][2] * rot[2][0] + m[1][2] * rot[2][1] + m[2][2] * rot[2][2];
    res[3][2] = m[3][2];

    res[0][3] = m[0][3];
    res[1][3] = m[1][3];
    res[2][3] = m[2][3];
    res[3][3] = m[3][3];

    return res;
}

[[nodiscard]] constexpr inline Matrix4f scale(const Matrix4f& m, const Vector3f& v) noexcept
{
    Matrix4f s(
        v.x,  0.0f, 0.0f, 0.0f,
        0.0f, v.y,  0.0f, 0.0f,
        0.0f, 0.0f, v.z,  0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    return m * s;
}

}

#endif