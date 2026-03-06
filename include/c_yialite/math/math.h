#ifndef C_YIALITE_MATH_H
#define C_YIALITE_MATH_H

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

typedef struct YiaLite_Vector2d
{
    double x;
    double y;
} YiaLite_Vector2d;

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

typedef struct YiaLite_Vector3d
{
    double x;
    double y;
    double z;
} YiaLite_Vector3d;

//Vector4
typedef struct YiaLite_Vector4f
{
    float x;
    float y;
    float z;
    float w;
} YiaLite_Vector4f;

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

#endif