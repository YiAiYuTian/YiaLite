#ifndef YIALITE_EVENT_BUS_H
#define YIALITE_EVENT_BUS_H

#include "event_abstract.h"
#include "../utils/containers/yia_array.h"
#include "../utils/containers/yia_list.h"

namespace yialite
{

typedef Uint32  EventTypeID;
typedef Uint8   EventPriorityID;
typedef Uint64  EventCallbackID;

inline constexpr EventCallbackID INVALID_EVENT_CALLBACK_UID = 0;

struct Subscription
{
    EventTypeID event_type_id = 0;
    EventPriorityID prio_id = 0;
    EventCallbackID callback_id = INVALID_EVENT_CALLBACK_UID;
};

class EventBus
{
private:
    using EventHandle = Delegate<void(IEvent&)>;

    struct WrappedHandle
    {
        EventCallbackID id = INVALID_EVENT_CALLBACK_UID;
        EventHandle callback;
        bool dead = false;
    };

    struct WrappedHandleGroup
    {
        List<WrappedHandle> handles[EVENT_PRIORITY_COUNT];
    };
public:
    EventBus() = default;
    ~EventBus() = default;
    EventBus(EventBus&&) = delete;
    EventBus(const EventBus&) = delete;

    //operators
    EventBus& operator=(EventBus&&) = delete;
    EventBus& operator=(const EventBus&) = delete;

    //tools
    template<typename T>
    Subscription subscribe(EventPriority prio, Delegate<void(const T&)> callback)
    {
        const EventTypeID event_type_id = static_cast<EventTypeID>(get_event_type_enum<T>());
        const EventPriorityID priority_id = static_cast<EventPriorityID>(prio);
        const EventCallbackID callback_id = ++m_next_id;

        EventHandle wrapper = 
            [cb = std::move(callback)](IEvent& e) -> void
            {
                cb(static_cast<const T&>(e));
            };

        auto& wrapped_handle_group = m_groups[event_type_id];
        wrapped_handle_group.handles[priority_id].emplace_back(callback_id, std::move(wrapper));

        return { event_type_id, priority_id, callback_id };
    }

    template<typename T>
    Subscription subscribe(Delegate<void(const T&)> callback)
    {
        return subscribe<T>(EventPriority::GameLogic, std::move(callback));
    }

    template<typename T>
    void callback_once(EventPriority prio, Delegate<void(const T&)> callback)
    {
        const EventTypeID event_type_id = static_cast<EventTypeID>(get_event_type_enum<T>());
        const EventPriorityID priority_id = static_cast<EventPriorityID>(prio);
        const EventCallbackID callback_id = ++m_next_id;

        EventHandle wrapper = 
            [cb = std::move(callback), this, event_type_id, priority_id, callback_id](IEvent& e) -> void
            {
                cb(static_cast<const T&>(e));
                this->unsubscribe({ event_type_id, priority_id, callback_id });
            };
        
        auto& wrapped_handle_group = m_groups[event_type_id];
        wrapped_handle_group.handles[priority_id].emplace_back(callback_id, std::move(wrapper));
    }

    template<typename T>
    void callback_once(Delegate<void(const T&)> callback)
    {
        callback_once<T>(EventPriority::GameLogic, std::move(callback));
    }

    void unsubscribe(const Subscription& sp)
    {
        if(sp.callback_id == INVALID_EVENT_CALLBACK_UID) return;
        mark_dead(sp);
    }

    void publish(IEvent& event)
    {
        auto& group = m_groups[static_cast<EventTypeID>(event.get_type())];

        for (size_t prio = 0; prio < EVENT_PRIORITY_COUNT; ++prio)
        {
            auto& handle_list = group.handles[prio];
            for (auto it = handle_list.begin(); it != handle_list.end(); )
            {
                if (event.consumed) return;
                if (it->dead)
                {
                    it = handle_list.erase(it);
                    continue;
                }
                it->callback(event);
                ++it;
            }

            if(handle_list.need_shrink()) handle_list.shrink_to_fit();
        }
    }

    void clear()
    {
        for (auto& group : m_groups)
        {
            for (size_t i = 0; i < EVENT_PRIORITY_COUNT; ++i)
            {
                group.handles[i].clear();
            }
        }
        m_next_id = INVALID_EVENT_CALLBACK_UID;
    }
private:
    void mark_dead(const Subscription& sp)
    {
        auto& handle_list = m_groups[static_cast<size_t>(sp.event_type_id)].handles[sp.prio_id];
        for (auto& h : handle_list)
        {
            if (h.id == sp.callback_id) { h.dead = true; return; }
        }
    }
private:
    Array<WrappedHandleGroup, static_cast<size_t>(EventType::Max)> m_groups;

    EventCallbackID m_next_id = INVALID_EVENT_CALLBACK_UID;
};

}

#endif