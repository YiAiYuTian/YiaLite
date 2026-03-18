#ifndef YIALITE_MATH_H
#define YIALITE_MATH_H

#include <cassert>
#include <cmath>
#include <limits>

#define TOLERANCE_SCALE 10

namespace yialite
{

//Vector2
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
            assert(std::abs(scalar) > std::numeric_limits<T>::epsilon() * TOLERANCE_SCALE && "Vector2 division by zero!");
        } else {
            assert(scalar != 0 && "Vector2 division by zero!");
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
            assert(std::abs(scalar) > std::numeric_limits<T>::epsilon() * TOLERANCE_SCALE && "Vector2 division by zero!");
        } else {
            assert(scalar != 0 && "Vector2 division by zero!");
        }
        
        T inv = static_cast<T>(1) / scalar;
        self[0] *= inv;
        self[1] *= inv;

        return self;
    }

    [[nodiscard]] constexpr T lengthSquared() const noexcept
    requires(std::is_floating_point_v<T>)
    {
        const Derived& self = static_cast<const Derived&>(*this);
        return self[0]*self[0] + self[1]*self[1];
    }

    [[nodiscard]] constexpr T length() const noexcept
    requires(std::is_floating_point_v<T>)
    {
        return std::sqrt(lengthSquared());
    }

    [[nodiscard]] constexpr Derived normalized() const noexcept
    requires(std::is_floating_point_v<T>)
    {
        const Derived& self = static_cast<const Derived&>(*this);
        T len = length();
        if (len < std::numeric_limits<T>::epsilon() * TOLERANCE_SCALE) return Derived{0};
        return self / len;
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

    constexpr void normalize() noexcept
    {
        float len = length();
        if (len < std::numeric_limits<float>::epsilon() * TOLERANCE_SCALE) return;
        *this /= len;
    }

    constexpr float& operator[](int i) noexcept 
    {
        assert(i >= 0 && i < 2 && "Vector2f index out of bounds!");
        return (&x)[i];
    }
    constexpr const float& operator[](int i) const noexcept 
    {
        assert(i >= 0 && i < 2 && "Vector2f index out of bounds!");
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
        assert(i >= 0 && i < 2 && "Vector2i index out of bounds!");
        return (&x)[i]; 
    }
    constexpr const int& operator[](int i) const noexcept 
    {
        assert(i >= 0 && i < 2 && "Vector2i index out of bounds!");
        return (&x)[i];
    }
};

//Vector3
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
            assert(std::abs(scalar) > std::numeric_limits<T>::epsilon() * TOLERANCE_SCALE && "Vector3 division by zero!");
        } else {
            assert(scalar != 0 && "Vector3 division by zero!");
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
            assert(std::abs(scalar) > std::numeric_limits<T>::epsilon() * TOLERANCE_SCALE && "Vector3 division by zero!");
        } else {
            assert(scalar != 0 && "Vector3 division by zero!");
        }
        
        T inv = static_cast<T>(1) / scalar;
        self[0] *= inv;
        self[1] *= inv;
        self[2] *= inv;

        return self;
    }

    [[nodiscard]] constexpr T lengthSquared() const noexcept
    requires(std::is_floating_point_v<T>)
    {
        const Derived& self = static_cast<const Derived&>(*this);
        return self[0]*self[0] + self[1]*self[1] + self[2]*self[2];
    }

    [[nodiscard]] constexpr T length() const noexcept
    requires(std::is_floating_point_v<T>)
    {
        return std::sqrt(lengthSquared());
    }

    [[nodiscard]] constexpr Derived normalized() const noexcept
    requires(std::is_floating_point_v<T>)
    {
        const Derived& self = static_cast<const Derived&>(*this);
        T len = length();
        if (len < std::numeric_limits<T>::epsilon() * TOLERANCE_SCALE) return Derived{0};
        return self / len;
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

    constexpr void normalize() noexcept
    {
        float len = length();
        if (len < std::numeric_limits<float>::epsilon() * TOLERANCE_SCALE) return;
        *this /= len;
    }

    constexpr float& operator[](int i) noexcept 
    {
        assert(i >= 0 && i < 3 && "Vector3f index out of bounds!");
        return (&x)[i];
    }
    constexpr const float& operator[](int i) const noexcept 
    {
        assert(i >= 0 && i < 3 && "Vector3f index out of bounds!");
        return (&x)[i];
    }
};

struct Vector3i : public Vector3Base<int, Vector3i>
{
    int x, y, z;

    constexpr Vector3i() : x(0), y(0), z(0) {}
    constexpr explicit Vector3i(int v) : x(v), y(v), z(v) {}
    constexpr Vector3i(int x_, int y_, int z_) : x(x_), y(y_), z(z_) {}

    constexpr int& operator[](int i) noexcept 
    {
        assert(i >= 0 && i < 3 && "Vector3i index out of bounds!");
        return (&x)[i];
    }
    constexpr const int& operator[](int i) const noexcept 
    {
        assert(i >= 0 && i < 3 && "Vector3i index out of bounds!");
        return (&x)[i];
    }
};

//Vector4Tag
struct Vector4Tag {};
struct RectTag {};
struct ColorTag {};

//Vector4
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
            assert(std::abs(scalar) > std::numeric_limits<T>::epsilon() * TOLERANCE_SCALE && "Vector4 division by zero!");
        } else {
            assert(scalar != 0 && "Vector4 division by zero!");
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
            assert(std::abs(scalar) > std::numeric_limits<T>::epsilon() * TOLERANCE_SCALE && "Vector4 division by zero!");
        } else {
            assert(scalar != 0 && "Vector4 division by zero!");
        }
        
        T inv = static_cast<T>(1) / scalar;
        self[0] *= inv;
        self[1] *= inv;
        self[2] *= inv;
        self[3] *= inv;

        return self;
    }

    [[nodiscard]] constexpr T lengthSquared() const noexcept
    requires(std::is_floating_point_v<T> && std::is_same_v<Tag, Vector4Tag>)
    {
        const Derived& self = static_cast<const Derived&>(*this);
        return self[0]*self[0] + self[1]*self[1] + self[2]*self[2] + self[3]*self[3];
    }

    [[nodiscard]] constexpr T length() const noexcept
    requires(std::is_floating_point_v<T> && std::is_same_v<Tag, Vector4Tag>)
    {
        return std::sqrt(lengthSquared());
    }

    [[nodiscard]] constexpr Derived normalized() const noexcept
    requires(std::is_floating_point_v<T> && std::is_same_v<Tag, Vector4Tag>)
    {
        const Derived& self = static_cast<const Derived&>(*this);
        T len = length();
        if (len < std::numeric_limits<T>::epsilon() * TOLERANCE_SCALE) return Derived{0};
        return self / len;
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

    constexpr void normalize() noexcept
    {
        float len = length();
        if (len < std::numeric_limits<float>::epsilon() * TOLERANCE_SCALE) return;
        *this /= len;
    }

    constexpr float& operator[](int i) noexcept 
    {
        assert(i >= 0 && i < 4 && "Vector4f index out of bounds!");
        return (&x)[i];
    }
    constexpr const float& operator[](int i) const noexcept 
    {
        assert(i >= 0 && i < 4 && "Vector4f index out of bounds!");
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
        assert(i >= 0 && i < 4 && "Vector4i index out of bounds!");
        return (&x)[i];
    }
    constexpr const int& operator[](int i) const noexcept 
    {
        assert(i >= 0 && i < 4 && "Vector4i index out of bounds!");
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
        assert(i >= 0 && i < 4 && "Rect index out of bounds!");
        return (&x)[i];
    }
    constexpr const int& operator[](int i) const noexcept 
    {
        assert(i >= 0 && i < 4 && "Rect index out of bounds!");
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
        assert(i >= 0 && i < 4 && "FRect index out of bounds!");
        return (&x)[i];
    }
    constexpr const float& operator[](int i) const noexcept 
    {
        assert(i >= 0 && i < 4 && "FRect index out of bounds!");
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
        assert(i >= 0 && i < 4 && "Color index out of bounds!");
        return (&r)[i];
    }
    constexpr const unsigned char& operator[](int i) const noexcept 
    {
        assert(i >= 0 && i < 4 && "Color index out of bounds!");
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
        assert(i >= 0 && i < 4 && "FColor index out of bounds!");
        return (&r)[i];
    }
    constexpr const float& operator[](int i) const noexcept 
    {
        assert(i >= 0 && i < 4 && "FColor index out of bounds!");
        return (&r)[i];
    }
};

//mat3
template<typename T, typename Derived>
struct Matrix3Base
{
    [[nodiscard]] constexpr Derived operator-() const noexcept
    {
        auto& self = static_cast<const Derived&>(*this);
        return Derived(
            -self[0][0], -self[1][0], -self[2][0],
            -self[0][1], -self[1][1], -self[2][1],
            -self[0][2], -self[1][2], -self[2][2]
        );
    }

    [[nodiscard]] constexpr Derived operator+(const Derived &other) const noexcept
    {
        auto& self = static_cast<const Derived&>(*this);

        return Derived(
            self[0][0] + other[0][0], self[1][0] + other[1][0], self[2][0] + other[2][0],
            self[0][1] + other[0][1], self[1][1] + other[1][1], self[2][1] + other[2][1],
            self[0][2] + other[0][2], self[1][2] + other[1][2], self[2][2] + other[2][2]
        );
    }

    [[nodiscard]] constexpr Derived operator-(const Derived& other) const noexcept
    {
        auto& self = static_cast<const Derived&>(*this);

        return Derived(
            self[0][0] - other[0][0], self[1][0] - other[1][0], self[2][0] - other[2][0],
            self[0][1] - other[0][1], self[1][1] - other[1][1], self[2][1] - other[2][1],
            self[0][2] - other[0][2], self[1][2] - other[1][2], self[2][2] - other[2][2]
        );
    }

    [[nodiscard]] constexpr Derived operator*(T scalar) const noexcept
    {
        auto& self = static_cast<const Derived&>(*this);

        return Derived(
            self[0][0] * scalar, self[1][0] * scalar, self[2][0] * scalar,
            self[0][1] * scalar, self[1][1] * scalar, self[2][1] * scalar,
            self[0][2] * scalar, self[1][2] * scalar, self[2][2] * scalar
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
    const auto& self = static_cast<const Derived&>(lhs);
    const auto& other = static_cast<const Derived&>(rhs);

    return Derived(
        self[0][0] * other[0][0] + self[0][1] * other[1][0] + self[0][2] * other[2][0],
        self[1][0] * other[0][0] + self[1][1] * other[1][0] + self[1][2] * other[2][0],
        self[2][0] * other[0][0] + self[2][1] * other[1][0] + self[2][2] * other[2][0],

        self[0][0] * other[0][1] + self[0][1] * other[1][1] + self[0][2] * other[2][1],
        self[1][0] * other[0][1] + self[1][1] * other[1][1] + self[1][2] * other[2][1],
        self[2][0] * other[0][1] + self[2][1] * other[1][1] + self[2][2] * other[2][1],

        self[0][0] * other[0][2] + self[0][1] * other[1][2] + self[0][2] * other[2][2],
        self[1][0] * other[0][2] + self[1][1] * other[1][2] + self[1][2] * other[2][2],
        self[2][0] * other[0][2] + self[2][1] * other[1][2] + self[2][2] * other[2][2]
    );
}

struct Matrix3f : public Matrix3Base<float, Matrix3f>
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
    constexpr Matrix3f(float m00, float m01, float m02,
                       float m10, float m11, float m12,
                       float m20, float m21, float m22)
    : data{{m00, m10, m20},
           {m01, m11, m21},
           {m02, m12, m22}} {}

    [[nodiscard]] constexpr Vector3f operator*(const Vector3f& other) const noexcept
    {
        return Vector3f(
            data[0][0] * other[0] + data[1][0] * other[1] + data[2][0] * other[2],
            data[0][1] * other[0] + data[1][1] * other[1] + data[2][1] * other[2],
            data[0][2] * other[0] + data[1][2] * other[1] + data[2][2] * other[2]
        );
    }

    constexpr float* operator[](int i) noexcept
    {
        assert(i >= 0 && i < 3 && "Matrix3f index out of bounds!");
        return data[i];
    }
    constexpr const float* operator[](int i) const noexcept 
    {
        assert(i >= 0 && i < 3 && "Matrix3f index out of bounds!");
        return data[i];
    }
};

//mat4
template<typename T, typename Derived>
struct Matrix4Base
{
    [[nodiscard]] constexpr Derived operator-() const noexcept
    {
        auto& self = static_cast<const Derived&>(*this);
        return Derived(
            -self[0][0], -self[1][0], -self[2][0], -self[3][0],
            -self[0][1], -self[1][1], -self[2][1], -self[3][1],
            -self[0][2], -self[1][2], -self[2][2], -self[3][2],
            -self[0][3], -self[1][3], -self[2][3], -self[3][3]
        );
    }

    [[nodiscard]] constexpr Derived operator+(const Derived &other) const noexcept
    {
        auto& self = static_cast<const Derived&>(*this);

        return Derived(
            self[0][0] + other[0][0], self[1][0] + other[1][0], self[2][0] + other[2][0], self[3][0] + other[3][0],
            self[0][1] + other[0][1], self[1][1] + other[1][1], self[2][1] + other[2][1], self[3][1] + other[3][1],
            self[0][2] + other[0][2], self[1][2] + other[1][2], self[2][2] + other[2][2], self[3][2] + other[3][2],
            self[0][3] + other[0][3], self[1][3] + other[1][3], self[2][3] + other[2][3], self[3][3] + other[3][3]
        );
    }

    [[nodiscard]] constexpr Derived operator-(const Derived& other) const noexcept
    {
        auto& self = static_cast<const Derived&>(*this);

        return Derived(
            self[0][0] - other[0][0], self[1][0] - other[1][0], self[2][0] - other[2][0], self[3][0] - other[3][0],
            self[0][1] - other[0][1], self[1][1] - other[1][1], self[2][1] - other[2][1], self[3][1] - other[3][1],
            self[0][2] - other[0][2], self[1][2] - other[1][2], self[2][2] - other[2][2], self[3][2] - other[3][2],
            self[0][3] - other[0][3], self[1][3] - other[1][3], self[2][3] - other[2][3], self[3][3] - other[3][3]
        );
    }

    [[nodiscard]] constexpr Derived operator*(T scalar) const noexcept
    {
        auto& self = static_cast<const Derived&>(*this);

        return Derived(
            self[0][0] * scalar, self[1][0] * scalar, self[2][0] * scalar, self[3][0] * scalar,
            self[0][1] * scalar, self[1][1] * scalar, self[2][1] * scalar, self[3][1] * scalar,
            self[0][2] * scalar, self[1][2] * scalar, self[2][2] * scalar, self[3][2] * scalar,
            self[0][3] * scalar, self[1][3] * scalar, self[2][3] * scalar, self[3][3] * scalar
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
    const auto& self = static_cast<const Derived&>(lhs);
    const auto& other = static_cast<const Derived&>(rhs);

    return Derived(
        self[0][0] * other[0][0] + self[0][1] * other[1][0] + self[0][2] * other[2][0] + self[0][3] * other[3][0],
        self[1][0] * other[0][0] + self[1][1] * other[1][0] + self[1][2] * other[2][0] + self[1][3] * other[3][0],
        self[2][0] * other[0][0] + self[2][1] * other[1][0] + self[2][2] * other[2][0] + self[2][3] * other[3][0],
        self[3][0] * other[0][0] + self[3][1] * other[1][0] + self[3][2] * other[2][0] + self[3][3] * other[3][0],

        self[0][0] * other[0][1] + self[0][1] * other[1][1] + self[0][2] * other[2][1] + self[0][3] * other[3][1],
        self[1][0] * other[0][1] + self[1][1] * other[1][1] + self[1][2] * other[2][1] + self[1][3] * other[3][1],
        self[2][0] * other[0][1] + self[2][1] * other[1][1] + self[2][2] * other[2][1] + self[2][3] * other[3][1],
        self[3][0] * other[0][1] + self[3][1] * other[1][1] + self[3][2] * other[2][1] + self[3][3] * other[3][1],

        self[0][0] * other[0][2] + self[0][1] * other[1][2] + self[0][2] * other[2][2] + self[0][3] * other[3][2],
        self[1][0] * other[0][2] + self[1][1] * other[1][2] + self[1][2] * other[2][2] + self[1][3] * other[3][2],
        self[2][0] * other[0][2] + self[2][1] * other[1][2] + self[2][2] * other[2][2] + self[2][3] * other[3][2],
        self[3][0] * other[0][2] + self[3][1] * other[1][2] + self[3][2] * other[2][2] + self[3][3] * other[3][2],

        self[0][0] * other[0][3] + self[0][1] * other[1][3] + self[0][2] * other[2][3] + self[0][3] * other[3][3],
        self[1][0] * other[0][3] + self[1][1] * other[1][3] + self[1][2] * other[2][3] + self[1][3] * other[3][3],
        self[2][0] * other[0][3] + self[2][1] * other[1][3] + self[2][2] * other[2][3] + self[2][3] * other[3][3],
        self[3][0] * other[0][3] + self[3][1] * other[1][3] + self[3][2] * other[2][3] + self[3][3] * other[3][3]
    );
}

struct Matrix4f : public Matrix4Base<float, Matrix4f>
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
    constexpr Matrix4f(float m00, float m01, float m02, float m03,
                       float m10, float m11, float m12, float m13,
                       float m20, float m21, float m22, float m23,
                       float m30, float m31, float m32, float m33)
    : data{{m00, m10, m20, m30},
           {m01, m11, m21, m31},
           {m02, m12, m22, m32},
           {m03, m13, m23, m33}} {}

    [[nodiscard]] constexpr Vector4f operator*(const Vector4f& other) const noexcept
    {
        return Vector4f(
            data[0][0] * other[0] + data[1][0] * other[1] + data[2][0] * other[2] + data[3][0] * other[3],
            data[0][1] * other[0] + data[1][1] * other[1] + data[2][1] * other[2] + data[3][1] * other[3],
            data[0][2] * other[0] + data[1][2] * other[1] + data[2][2] * other[2] + data[3][2] * other[3],
            data[0][3] * other[0] + data[1][3] * other[1] + data[2][3] * other[2] + data[3][3] * other[3]
        );
    }

    constexpr float* operator[](int i) noexcept
    {
        assert(i >= 0 && i < 4 && "Matrix4f index out of bounds!");
        return data[i];
    }
    constexpr const float* operator[](int i) const noexcept 
    {
        assert(i >= 0 && i < 4 && "Matrix4f index out of bounds!");
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

}

#endif