#ifndef YIALITE_RESULT_EXPORT_H
#define YIALITE_RESULT_EXPORT_H

#include "result.h"

namespace yialite
{

class Context;
extern template class Result<Context*>;

class WindowManager;
extern template class Result<WindowManager*>;

class Renderer2D;
extern template class Result<Renderer2D*>;

class Texture2D;
extern template class Result<Texture2D*>;

class EventManager;
extern template class Result<EventManager*>;

class DevUI;
extern template class Result<DevUI*>;

class AudioManager;
extern template class Result<AudioManager*>;

}

#endif