#ifndef YIALITE_EVENT_BUS_H
#define YIALITE_EVENT_BUS_H

#include "event_abstract.h"
#include "../utils/containers/yia_array.h"
#include "../utils/containers/yia_list.h"

namespace yialite
{

using EventHandle = Delegate<void(IEvent&)>;

struct HandleGroup
{
    List<EventHandle> handles[EVENT_PRIORITY_COUNT];
};

class EventBus
{
public:
    EventBus() = default;
    ~EventBus() = default;
    EventBus(const EventBus&) = delete;
    EventBus(EventBus&& other) noexcept : m_groups(std::move(other.m_groups)) {}

    //operators
    EventBus& operator=(const EventBus&) = delete;
    EventBus& operator=(EventBus&& other) noexcept
    {
        if(this == &other) return *this; 

        m_groups = std::move(other.m_groups);
        return *this;
    }

    //tools
    template<typename T>
    void subscribe(EventPriority prio, Delegate<void(const T&)> callback)
    {
        EventHandle wrapper = 
            [cb = std::move(callback)](IEvent& e) -> void
            {
                cb(static_cast<const T&>(e));
            };

        const size_t idx = static_cast<size_t>(prio);
        const size_t type_idx = static_cast<size_t>(get_event_type_enum<T>());
        m_groups[type_idx].handles[idx].emplace_back(std::move(wrapper));
    }

    template<typename T>
    void subscribe(Delegate<void(const T&)> callback)
    {
        subscribe<T>(EventPriority::GameLogic, std::move(callback));
    }

    void publish(IEvent& event)
    {
        auto& group = m_groups[static_cast<size_t>(event.get_type())];
        for (size_t prio = 0; prio < EVENT_PRIORITY_COUNT; ++prio)
        {
            auto& handle_list = group.handles[prio];
            for (auto& handle : handle_list)
            {
                if (event.consumed) return;
                handle(event);
            }
        }
    }

    void clear()
    {
        for (auto& g : m_groups)
        {
            for (auto& list : g.handles) list.clear();
        }
    }
private:
    Array<HandleGroup, static_cast<size_t>(EventType::Max)> m_groups;
};

}

#endif