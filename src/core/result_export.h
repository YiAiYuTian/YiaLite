#ifndef YIALITE_RESULT_EXPORT_H
#define YIALITE_RESULT_EXPORT_H

#include "result.h"

namespace yialite
{

class Context;
extern template class Result<Context*>;

class Window;
extern template class Result<Window*>;

class Renderer2D;
extern template class Result<Renderer2D*>;

class Texture2D;
extern template class Result<Texture2D*>;

class Event;
extern template class Result<Event*>;

class DevUI;
extern template class Result<DevUI*>;

class AudioManager;
extern template class Result<AudioManager*>;

}

#endif