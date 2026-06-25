#include "pch.h"
#include "result_export.h"

namespace yialite
{

template class YIALITE_API Result<Context*>;
template class YIALITE_API Result<WindowManager*>;
template class YIALITE_API Result<Renderer2D*>;
template class YIALITE_API Result<Texture2D*>;
template class YIALITE_API Result<EventManager*>;
template class YIALITE_API Result<DevUI*>;
template class YIALITE_API Result<AudioManager*>;

}