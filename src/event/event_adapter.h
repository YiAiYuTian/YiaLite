#ifndef YIALITE_EVENT_ADAPTER_H
#define YIALITE_EVENT_ADAPTER_H

namespace yialite
{

class EventBus;

class IEventAdapter
{
public:
    virtual ~IEventAdapter() = default;

    virtual void poll_event(EventBus& bus, bool has_devui) = 0;
};

}

#endif