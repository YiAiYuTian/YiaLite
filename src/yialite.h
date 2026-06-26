#ifndef YIALITE_H
#define YIALITE_H

//core
#include "core/core.h"
#include "core/error.h"
#include "core/result.h"
#include "core/initialize.h"
#include "core/context.h"
#include "core/log.h"

//audio
#include "audio/audio_manager.h"

//event
#include "event/event_manager.h"
#include "event/event_listener.h"

//input
#include "input/input.h"

//renderer
#include "renderer/renderer2d.h"
#include "renderer/texture/texture2d.h"

//window
#include "window/window_manager.h"

//devui
#include "devui/devui.h"
//#include <imgui.h>

//utils
#include "utils/singleton.h"
#include "utils/delegate.h"
#include "utils/memory/allocator.h"
#include "utils/memory/memory.h"
#include "utils/string/yia_string.h"
#include "utils/containers/yia_list.h"
#include "utils/containers/yia_hashmap.h"
#include "utils/containers/yia_array.h"

#endif
