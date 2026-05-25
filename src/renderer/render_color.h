#ifndef YIALITE_RENDERER_COLOR_H
#define YIALITE_RENDERER_COLOR_H

#include "../math/math.h"

namespace yialite 
{

//color
constexpr Color COLOR_WHITE          = { 255, 255, 255, 255 };
constexpr Color COLOR_BLACK          = {   0,   0,   0, 255 };
constexpr Color COLOR_RED            = { 255,   0,   0, 255 };
constexpr Color COLOR_GREEN          = {   0, 255,   0, 255 };
constexpr Color COLOR_BLUE           = {   0,   0, 255, 255 };
constexpr Color COLOR_YELLOW         = { 255, 255,   0, 255 };
constexpr Color COLOR_CYAN           = {   0, 255, 255, 255 };
constexpr Color COLOR_MAGENTA        = { 255,   0, 255, 255 };
constexpr Color COLOR_GRAY           = { 128, 128, 128, 255 };
constexpr Color COLOR_LIGHT_GRAY     = { 192, 192, 192, 255 };
constexpr Color COLOR_DARK_GRAY      = {  64,  64,  64, 255 };
constexpr Color COLOR_TRANSPARENT    = {   0,   0,   0,   0 };
constexpr Color COLOR_DEFAULT        = COLOR_WHITE;

//fcolor
constexpr FColor FCOLOR_WHITE        = { 1.0f,  1.0f,  1.0f,  1.0f };
constexpr FColor FCOLOR_BLACK        = { 0.0f,  0.0f,  0.0f,  1.0f };
constexpr FColor FCOLOR_RED          = { 1.0f,  0.0f,  0.0f,  1.0f };
constexpr FColor FCOLOR_GREEN        = { 0.0f,  1.0f,  0.0f,  1.0f };
constexpr FColor FCOLOR_BLUE         = { 0.0f,  0.0f,  1.0f,  1.0f };
constexpr FColor FCOLOR_YELLOW       = { 1.0f,  1.0f,  0.0f,  1.0f };
constexpr FColor FCOLOR_CYAN         = { 0.0f,  1.0f,  1.0f,  1.0f };
constexpr FColor FCOLOR_MAGENTA      = { 1.0f,  0.0f,  1.0f,  1.0f };
constexpr FColor FCOLOR_GRAY         = { 0.5f,  0.5f,  0.5f,  1.0f };
constexpr FColor FCOLOR_LIGHT_GRAY   = { 0.75f, 0.75f, 0.75f, 1.0f };
constexpr FColor FCOLOR_DARK_GRAY    = { 0.25f, 0.25f, 0.25f, 1.0f };
constexpr FColor FCOLOR_TRANSPARENT  = { 0.0f,  0.0f,  0.0f,  0.0f };
constexpr FColor FCOLOR_DEFAULT      = FCOLOR_WHITE;

}

#endif