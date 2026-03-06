#ifndef YIALITE_MATH_H
#define YIALITE_MATH_H

namespace yialite
{

//Vector2
template<typename T>
struct Vector2
{
    T x;
    T y;
};

using Vector2i = Vector2<int>;
using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;

//Vector3
template<typename T>
struct Vector3
{
    T x;
    T y;
    T z;
};

using Vector3i = Vector3<int>;
using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;

//Vector4 Tag
struct DefaultVector4Tag {};
struct RectVector4Tag {};
struct FRectVector4Tag {};
struct ColorVector4Tag {};
struct FColorVector4Tag {};

//Vector4
template<typename T, typename Tag = DefaultVector4Tag>
struct Vector4
{
    T x;
    T y;
    T z;
    T w;
};

template<>
struct Vector4<int, RectVector4Tag>
{
    int x;
    int y;
    int w;
    int h;
};

template<>
struct Vector4<float, FRectVector4Tag>
{
    float x;
    float y;
    float w;
    float h;
};

template<>
struct Vector4<unsigned char, ColorVector4Tag>
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

template<>
struct Vector4<float, FColorVector4Tag>
{
    float r;
    float g;
    float b;
    float a;
};

using Vector4i = Vector4<int>;
using Vector4f = Vector4<float>;
using Rect = Vector4<int, RectVector4Tag>;
using FRect = Vector4<float, FRectVector4Tag>;
using Color = Vector4<unsigned char, ColorVector4Tag>;
using FColor = Vector4<float, FColorVector4Tag>;

}

#endif