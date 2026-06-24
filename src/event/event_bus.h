#ifndef YIALITE_EVENT_BUS_H
#define YIALITE_EVENT_BUS_H

#include "event_abstract.h"
#include "../utils/containers/yia_hashmap.h"
#include "../utils/containers/yia_list.h"

namespace yialite
{

typedef Uint32  EventTypeID;
typedef Uint8   EventPriorityID;
typedef Uint64  EventCallbackUID;

constexpr EventCallbackUID EVENT_CALLBACK_UID_INVALID = 0;

struct Subscription
{
    EventTypeID event_type_id = 0;
    EventPriorityID prio_id = 0;
    EventCallbackUID callback_uid = EVENT_CALLBACK_UID_INVALID;
};

class EventBus
{
private:
    using EventHandle = Delegate<void(IEvent&)>;

    struct WrappedHandle
    {
        EventCallbackUID uid;
        EventHandle callback;
    };

    struct WrappedHandleGroup
    {
        List<WrappedHandle> handles[EVENT_PRIORITY_COUNT];
    };
public:
    EventBus() = default;
    ~EventBus() = default;
    EventBus(const EventBus&) = delete;
    EventBus(EventBus&& other) noexcept 
        : m_groups(std::move(other.m_groups)), m_uid_counter(other.m_uid_counter) 
    { 
        other.m_uid_counter = EVENT_CALLBACK_UID_INVALID; 
    }

    //operators
    EventBus& operator=(const EventBus&) = delete;
    EventBus& operator=(EventBus&& other) noexcept
    {
        if(this == &other) return *this; 

        m_groups = std::move(other.m_groups);
        m_uid_counter = other.m_uid_counter;
        other.m_uid_counter = EVENT_CALLBACK_UID_INVALID;
        return *this;
    }

    //tools
    template<typename T>
    Subscription subscribe(EventPriority prio, Delegate<void(const T&)> callback)
    {
        const EventTypeID event_type_id = static_cast<EventTypeID>(get_event_type_enum<T>());
        const EventPriorityID priority_id = static_cast<EventPriorityID>(prio);
        const EventCallbackUID callback_uid = ++m_uid_counter;

        EventHandle wrapper = 
            [cb = std::move(callback)](IEvent& e) -> void
            {
                cb(static_cast<const T&>(e));
            };

        auto& wrapped_handle_group = m_groups[event_type_id];
        wrapped_handle_group.handles[priority_id].emplace_back(callback_uid, std::move(wrapper));

        return { event_type_id, priority_id, callback_uid };
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
        const EventCallbackUID callback_uid = ++m_uid_counter;

        EventHandle wrapper = 
            [cb = std::move(callback), this, event_type_id, priority_id, callback_uid](IEvent& e) -> void
            {
                cb(static_cast<const T&>(e));
                this->unsubscribe({ event_type_id, priority_id, callback_uid });
            };
        
        auto& wrapped_handle_group = m_groups[event_type_id];
        wrapped_handle_group.handles[priority_id].emplace_back(callback_uid, std::move(wrapper));
    }

    template<typename T>
    void callback_once(Delegate<void(const T&)> callback)
    {
        callback_once<T>(EventPriority::GameLogic, std::move(callback));
    }

    void unsubscribe(const Subscription& sp)
    {
        if(sp.callback_uid == EVENT_CALLBACK_UID_INVALID) return;

        auto* group = m_groups.find(sp.event_type_id);
        if(!group) return;

        auto& handle_list = group->handles[sp.prio_id];
        handle_list.erase(std::remove_if(handle_list.begin(), handle_list.end(), 
            [uid = sp.callback_uid](const WrappedHandle& handle) -> bool
            {
                return handle.uid == uid;
            }
        ), handle_list.end());

        if(handle_list.need_shrink()) handle_list.shrink_to_fit();
    }

    void publish(IEvent& event)
    {
        auto* group = m_groups.find(static_cast<EventTypeID>(event.get_type()));
        if(!group) return;

        for (size_t prio = 0; prio < EVENT_PRIORITY_COUNT; ++prio)
        {
            auto handle_list_snapshot = group->handles[prio];
            for (auto& handle : handle_list_snapshot)
            {
                if (event.consumed) return;
                handle.callback(event);
            }
        }
    }

    void clear()
    {
        for (auto it = m_groups.begin(); it != m_groups.end(); ++it)
        {
            auto& group = it->second;
            for (size_t i = 0; i < EVENT_PRIORITY_COUNT; ++i)
            {
                group.handles[i].clear();
            }
        }
        m_groups.clear();
        m_uid_counter = EVENT_CALLBACK_UID_INVALID;
    }
private:
    HashMap<EventTypeID, WrappedHandleGroup> m_groups;

    EventCallbackUID m_uid_counter = EVENT_CALLBACK_UID_INVALID;
};

}

#endif