#ifndef C_YIALITE_RENDERER_COLOR_H
#define C_YIALITE_RENDERER_COLOR_H

#include "../math/math.h"

//color
#define YIALITE_COLOR_WHITE             ((YiaLite_Color){ 255, 255, 255, 255 })
#define YIALITE_COLOR_BLACK             ((YiaLite_Color){   0,   0,   0, 255 })
#define YIALITE_COLOR_RED               ((YiaLite_Color){ 255,   0,   0, 255 })
#define YIALITE_COLOR_GREEN             ((YiaLite_Color){   0, 255,   0, 255 })
#define YIALITE_COLOR_BLUE              ((YiaLite_Color){   0,   0, 255, 255 })
#define YIALITE_COLOR_YELLOW            ((YiaLite_Color){ 255, 255,   0, 255 })
#define YIALITE_COLOR_CYAN              ((YiaLite_Color){   0, 255, 255, 255 })
#define YIALITE_COLOR_MAGENTA           ((YiaLite_Color){ 255,   0, 255, 255 })
#define YIALITE_COLOR_GRAY              ((YiaLite_Color){ 128, 128, 128, 255 })
#define YIALITE_COLOR_LIGHT_GRAY        ((YiaLite_Color){ 192, 192, 192, 255 })
#define YIALITE_COLOR_DARK_GRAY         ((YiaLite_Color){  64,  64,  64, 255 })
#define YIALITE_COLOR_TRANSPARENT       ((YiaLite_Color){   0,   0,   0,   0 })
#define YIALITE_COLOR_DEFAULT           YIALITE_COLOR_WHITE

//fcolor
#define YIALITE_FCOLOR_WHITE            ((YiaLite_FColor){ 1.0f,  1.0f,  1.0f,  1.0f })
#define YIALITE_FCOLOR_BLACK            ((YiaLite_FColor){ 0.0f,  0.0f,  0.0f,  1.0f })
#define YIALITE_FCOLOR_RED              ((YiaLite_FColor){ 1.0f,  0.0f,  0.0f,  1.0f })
#define YIALITE_FCOLOR_GREEN            ((YiaLite_FColor){ 0.0f,  1.0f,  0.0f,  1.0f })
#define YIALITE_FCOLOR_BLUE             ((YiaLite_FColor){ 0.0f,  0.0f,  1.0f,  1.0f })
#define YIALITE_FCOLOR_YELLOW           ((YiaLite_FColor){ 1.0f,  1.0f,  0.0f,  1.0f })
#define YIALITE_FCOLOR_CYAN             ((YiaLite_FColor){ 0.0f,  1.0f,  1.0f,  1.0f })
#define YIALITE_FCOLOR_MAGENTA          ((YiaLite_FColor){ 1.0f,  0.0f,  1.0f,  1.0f })
#define YIALITE_FCOLOR_GRAY             ((YiaLite_FColor){ 0.5f,  0.5f,  0.5f,  1.0f })
#define YIALITE_FCOLOR_LIGHT_GRAY       ((YiaLite_FColor){ 0.75f, 0.75f, 0.75f, 1.0f })
#define YIALITE_FCOLOR_DARK_GRAY        ((YiaLite_FColor){ 0.25f, 0.25f, 0.25f, 1.0f })
#define YIALITE_FCOLOR_TRANSPARENT      ((YiaLite_FColor){ 0.0f,  0.0f,  0.0f,  0.0f })
#define YIALITE_FCOLOR_DEFAULT          YIALITE_FCOLOR_WHITE

#endif