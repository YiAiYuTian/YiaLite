#ifndef YIALITE_INITIALIZE_H
#define YIALITE_INITIALIZE_H

#include "core.h"
#include "result.h"

namespace yialite
{

YIALITE_API Result<void> init();
YIALITE_API void quit();

}

#endif
