#ifndef YIALITE_EVENT_MANAGER_H
#define YIALITE_EVENT_MANAGER_H

#include "event_bus.h"
#include "../core/result.h"

namespace yialite
{

class DevUI;
class IEventAdapter;

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

class YIALITE_API EventManager
{
public:
    ~EventManager();
    EventManager(EventManager&& other) noexcept;
    EventManager& operator=(EventManager&& other) noexcept;

    static Result<EventManager*> create();
    static void destroy(EventManager* mgr);

    void poll_event();
    void set_devui(DevUI* devui);

    template<typename T>
    void subscribe(EventPriority prio, Delegate<void(const T&)> cb)
    {
        m_bus.subscribe<T>(prio, std::move(cb));
    }
    template<typename T>
    void subscribe(Delegate<void(const T&)> cb)
    {
        m_bus.subscribe<T>(std::move(cb));
    }
private:
    EventManager() = default;
    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;
private:
    EventBus m_bus;
    IEventAdapter* m_evt_adapter = nullptr;
    bool has_devui = false;
};

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

}

#endif
