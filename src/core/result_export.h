#ifndef YIALITE_RESULT_EXPORT_H
#define YIALITE_RESULT_EXPORT_H

#include "result.h"

namespace yialite
{

class Context;
template class YIALITE_API Result<Context*>;

class Window;
template class YIALITE_API Result<Window*>;

class Renderer2D;
template class YIALITE_API Result<Renderer2D*>;

class Texture2D;
template class YIALITE_API Result<Texture2D*>;

class Event;
template class YIALITE_API Result<Event*>;

class DevUI;
template class YIALITE_API Result<DevUI*>;

class AudioManager;
template class YIALITE_API Result<AudioManager*>;

}

#endif