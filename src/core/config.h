#ifndef YIALITE_CONFIG_H
#define YIALITE_CONFIG_H

#include "../window/window_config.h"

namespace yialite
{

struct ContextConfig
{
    WindowConfig window_config;
    bool enable_devui = false;
};

}

#endif