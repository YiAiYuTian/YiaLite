#ifndef C_YIALITE_MATH_H
#define C_YIALITE_MATH_H

#include "../../cpp_api/core/core.h"

//Vector2
typedef struct YiaLite_Vector2f
{
    float x;
    float y;
} YiaLite_Vector2f;

typedef struct YiaLite_Vector2i
{
    int x;
    int y;
} YiaLite_Vector2i;

//Vector3
typedef struct YiaLite_Vector3f
{
    float x;
    float y;
    float z;
} YiaLite_Vector3f;

typedef struct YiaLite_Vector3i
{
    int x;
    int y;
    int z;
} YiaLite_Vector3i;

//Vector4
typedef struct YiaLite_Vector4f
{
    float x;
    float y;
    float z;
    float w;
} YiaLite_Vector4f;

typedef struct YiaLite_Vector4i
{
    int x;
    int y;
    int z;
    int w;
} YiaLite_Vector4i;

typedef struct YiaLite_Rect
{
    int x;
    int y;
    int w;
    int h;
} YiaLite_Rect;

typedef struct YiaLite_FRect
{
    float x;
    float y;
    float w;
    float h;
} YiaLite_FRect;

typedef struct YiaLite_Color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} YiaLite_Color;

typedef struct YiaLite_FColor
{
    float r;
    float g;
    float b;
    float a;
} YiaLite_FColor;

#ifdef __cplusplus
extern "C" {
#endif

//vector2
YIALITE_API YiaLite_Vector2f YiaLite_Vector2fAdd        (YiaLite_Vector2f a, YiaLite_Vector2f b);
YIALITE_API YiaLite_Vector2f YiaLite_Vector2fSub        (YiaLite_Vector2f a, YiaLite_Vector2f b);
YIALITE_API YiaLite_Vector2f YiaLite_Vector2fMul        (YiaLite_Vector2f v, float scalar);
YIALITE_API YiaLite_Vector2f YiaLite_Vector2fDiv        (YiaLite_Vector2f v, float scalar);
YIALITE_API YiaLite_Vector2f YiaLite_Vector2fNeg        (YiaLite_Vector2f v);
YIALITE_API float YiaLite_Vector2fLengthSquared         (YiaLite_Vector2f v);
YIALITE_API float YiaLite_Vector2fLength                (YiaLite_Vector2f v);
YIALITE_API void YiaLite_Vector2fNormalize              (YiaLite_Vector2f* v);
YIALITE_API YiaLite_Vector2f YiaLite_Vector2fNormalized (YiaLite_Vector2f v);

YIALITE_API YiaLite_Vector2i YiaLite_Vector2iAdd        (YiaLite_Vector2i a, YiaLite_Vector2i b);
YIALITE_API YiaLite_Vector2i YiaLite_Vector2iSub        (YiaLite_Vector2i a, YiaLite_Vector2i b);
YIALITE_API YiaLite_Vector2i YiaLite_Vector2iMul        (YiaLite_Vector2i v, int scalar);
YIALITE_API YiaLite_Vector2i YiaLite_Vector2iDiv        (YiaLite_Vector2i v, int scalar);
YIALITE_API YiaLite_Vector2i YiaLite_Vector2iNeg        (YiaLite_Vector2i v);

//vector3
YIALITE_API YiaLite_Vector3f YiaLite_Vector3fAdd        (YiaLite_Vector3f a, YiaLite_Vector3f b);
YIALITE_API YiaLite_Vector3f YiaLite_Vector3fSub        (YiaLite_Vector3f a, YiaLite_Vector3f b);
YIALITE_API YiaLite_Vector3f YiaLite_Vector3fMul        (YiaLite_Vector3f v, float scalar);
YIALITE_API YiaLite_Vector3f YiaLite_Vector3fDiv        (YiaLite_Vector3f v, float scalar);
YIALITE_API YiaLite_Vector3f YiaLite_Vector3fNeg        (YiaLite_Vector3f v);
YIALITE_API float YiaLite_Vector3fLengthSquared         (YiaLite_Vector3f v);
YIALITE_API float YiaLite_Vector3fLength                (YiaLite_Vector3f v);
YIALITE_API void YiaLite_Vector3fNormalize              (YiaLite_Vector3f* v);
YIALITE_API YiaLite_Vector3f YiaLite_Vector3fNormalized (YiaLite_Vector3f v);

YIALITE_API YiaLite_Vector3i YiaLite_Vector3iAdd        (YiaLite_Vector3i a, YiaLite_Vector3i b);
YIALITE_API YiaLite_Vector3i YiaLite_Vector3iSub        (YiaLite_Vector3i a, YiaLite_Vector3i b);
YIALITE_API YiaLite_Vector3i YiaLite_Vector3iMul        (YiaLite_Vector3i v, int scalar);
YIALITE_API YiaLite_Vector3i YiaLite_Vector3iDiv        (YiaLite_Vector3i v, int scalar);
YIALITE_API YiaLite_Vector3i YiaLite_Vector3iNeg        (YiaLite_Vector3i v);

//vector4
YIALITE_API YiaLite_Vector4f YiaLite_Vector4fAdd        (YiaLite_Vector4f a, YiaLite_Vector4f b);
YIALITE_API YiaLite_Vector4f YiaLite_Vector4fSub        (YiaLite_Vector4f a, YiaLite_Vector4f b);
YIALITE_API YiaLite_Vector4f YiaLite_Vector4fMul        (YiaLite_Vector4f v, float scalar);
YIALITE_API YiaLite_Vector4f YiaLite_Vector4fDiv        (YiaLite_Vector4f v, float scalar);
YIALITE_API YiaLite_Vector4f YiaLite_Vector4fNeg        (YiaLite_Vector4f v);
YIALITE_API float YiaLite_Vector4fLengthSquared         (YiaLite_Vector4f v);
YIALITE_API float YiaLite_Vector4fLength                (YiaLite_Vector4f v);
YIALITE_API void YiaLite_Vector4fNormalize              (YiaLite_Vector4f* v);
YIALITE_API YiaLite_Vector4f YiaLite_Vector4fNormalized (YiaLite_Vector4f v);

YIALITE_API YiaLite_Vector4i YiaLite_Vector4iAdd        (YiaLite_Vector4i a, YiaLite_Vector4i b);
YIALITE_API YiaLite_Vector4i YiaLite_Vector4iSub        (YiaLite_Vector4i a, YiaLite_Vector4i b);
YIALITE_API YiaLite_Vector4i YiaLite_Vector4iMul        (YiaLite_Vector4i v, int scalar);
YIALITE_API YiaLite_Vector4i YiaLite_Vector4iDiv        (YiaLite_Vector4i v, int scalar);
YIALITE_API YiaLite_Vector4i YiaLite_Vector4iNeg        (YiaLite_Vector4i v);

#ifdef __cplusplus
}
#endif

#endif