#ifndef YIALITE_SDL_EVENT_ADAPTER_H
#define YIALITE_SDL_EVENT_ADAPTER_H

#include "../../../event/event_adapter.h"

#include <SDL3/SDL_events.h>

namespace yialite
{

class SDLEventAdapter : public IEventAdapter
{
public:
    void poll_event(EventBus& bus, bool has_devui) override;
private:
    SDL_Event m_event;
};

}

#endif
