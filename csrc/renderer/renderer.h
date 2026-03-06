#ifndef C_YIALITE_RENDERER_H
#define C_YIALITE_RENDERER_H

#include "../../src/core/core.h"

#include "../math/math.h"

#define DEFAULT_COLOR ((YiaLite_Color){ 255, 255, 255, 255 })
#define DEFAULT_FCOLOR ((YiaLite_FColor){ 1.0f, 1.0f, 1.0f, 1.0f })

typedef struct YiaLite_Window YiaLite_Window;
typedef struct YiaLite_Renderer YiaLite_Renderer;

#ifdef __cplusplus
extern "C" {
#endif

YIALITE_API YiaLite_Renderer* YiaLite_CreateRenderer(YiaLite_Window* window);
YIALITE_API void YiaLite_DestroyRenderer(YiaLite_Renderer* renderer);

YIALITE_API void YiaLite_BeginDraw(YiaLite_Renderer* renderer, const YiaLite_Color background_color);
YIALITE_API void YiaLite_BeginDrawF(YiaLite_Renderer* renderer, const YiaLite_FColor background_fcolor);
YIALITE_API void YiaLite_EndDraw(YiaLite_Renderer* renderer);

YIALITE_API void YiaLite_DrawPoint       (YiaLite_Renderer* renderer, const YiaLite_Vector2f pos, const YiaLite_Color color);
YIALITE_API void YiaLite_DrawPoints      (YiaLite_Renderer* renderer, const YiaLite_Vector2f* pos, int count, const YiaLite_Color color);
YIALITE_API void YiaLite_DrawLine        (YiaLite_Renderer* renderer, const YiaLite_Vector2f start, const YiaLite_Vector2f end, const YiaLite_Color color);
YIALITE_API void YiaLite_DrawRectV       (YiaLite_Renderer* renderer, const YiaLite_Vector2f pos, const YiaLite_Vector2f size, const YiaLite_Color color);
YIALITE_API void YiaLite_DrawRectR       (YiaLite_Renderer* renderer, const YiaLite_FRect rect, const YiaLite_Color color);
YIALITE_API void YiaLite_DrawFillRectV   (YiaLite_Renderer* renderer, const YiaLite_Vector2f pos, const YiaLite_Vector2f size, const YiaLite_Color color);
YIALITE_API void YiaLite_DrawFillRectR   (YiaLite_Renderer* renderer, const YiaLite_FRect rect, const YiaLite_Color color);

YIALITE_API void YiaLite_DrawPointF      (YiaLite_Renderer* renderer, const YiaLite_Vector2f pos, const YiaLite_FColor fcolor);
YIALITE_API void YiaLite_DrawPointsF     (YiaLite_Renderer* renderer, const YiaLite_Vector2f* pos, int count, const YiaLite_FColor fcolor);
YIALITE_API void YiaLite_DrawLineF       (YiaLite_Renderer* renderer, const YiaLite_Vector2f start, const YiaLite_Vector2f end, const YiaLite_FColor fcolor);
YIALITE_API void YiaLite_DrawRectVF      (YiaLite_Renderer* renderer, const YiaLite_Vector2f pos, const YiaLite_Vector2f size, const YiaLite_FColor fcolor);
YIALITE_API void YiaLite_DrawRectRF      (YiaLite_Renderer* renderer, const YiaLite_FRect rect, const YiaLite_FColor fcolor);
YIALITE_API void YiaLite_DrawFillRectVF  (YiaLite_Renderer* renderer, const YiaLite_Vector2f pos, const YiaLite_Vector2f size, const YiaLite_FColor fcolor);
YIALITE_API void YiaLite_DrawFillRectRF  (YiaLite_Renderer* renderer, const YiaLite_FRect rect, const YiaLite_FColor fcolor);

#ifdef __cplusplus
}
#endif

#endif