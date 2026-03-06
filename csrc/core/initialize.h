#ifndef C_YIALITE_INITIALIZE_H
#define C_YIALITE_INITIALIZE_H

#include "../../src/core/core.h"

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

YIALITE_API bool YiaLite_Init();
YIALITE_API void YiaLite_Quit();

#ifdef __cplusplus
}
#endif

#endif