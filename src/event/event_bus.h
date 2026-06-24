#ifndef YIALITE_EVENT_BUS_H
#define YIALITE_EVENT_BUS_H

#include "event_abstract.h"
#include "../utils/containers/yia_hashmap.h"
#include "../utils/containers/yia_list.h"

namespace yialite
{

struct Subscription
{
    Uint32 event_type_id = 0;
    Uint8 prio_id = 0;
    Uint64 callback_uid = 0;
};

class EventBus
{
private:
    using EventHandle = Delegate<void(IEvent&)>;

    struct WrappedHandle
    {
        Uint64 uid;
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
        : m_groups(std::move(other.m_groups)), m_uid_counter(other.m_uid_counter) { other.m_uid_counter = 1; }

    //operators
    EventBus& operator=(const EventBus&) = delete;
    EventBus& operator=(EventBus&& other) noexcept
    {
        if(this == &other) return *this; 

        m_groups = std::move(other.m_groups);
        m_uid_counter = other.m_uid_counter;
        other.m_uid_counter = 1;
        return *this;
    }

    //tools
    template<typename T>
    Subscription subscribe(EventPriority prio, Delegate<void(const T&)> callback)
    {
        const Uint32 event_type_id = static_cast<Uint32>(get_event_type_enum<T>());
        const Uint8 priority_id = static_cast<Uint8>(prio);
        const Uint64 callback_uid = m_uid_counter++;

        EventHandle wrapper = 
            [cb = std::move(callback)](IEvent& e) -> void
            {
                cb(static_cast<const T&>(e));
            };

        auto& wrapped_handle_group = m_groups[event_type_id];
        wrapped_handle_group.handles.emplace_back(WrappedHandle{ callback_uid, std::move(wrapper) });

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
        const Uint32 event_type_id = static_cast<Uint32>(get_event_type_enum<T>());
        const Uint8 priority_id = static_cast<Uint8>(prio);
        const Uint64 callback_uid = m_uid_counter++;

        EventHandle wrapper = 
            [cb = std::move(callback), this, event_type_id, priority_id, callback_uid](IEvent& e) -> void
            {
                cb(static_cast<const T&>(e));
                this->unsubscribe({ event_type_id, priority_id, callback_uid });
            };
        
        auto& wrapped_handle_group = m_groups[event_type_id];
        wrapped_handle_group.handles.emplace_back(WrappedHandle{ callback_uid, std::move(wrapper) });
    }

    template<typename T>
    void callback_once(Delegate<void(const T&)> callback)
    {
        callback_once<T>(EventPriority::GameLogic, std::move(callback));
    }

    void unsubscribe(const Subscription& sp)
    {
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
        auto* group = m_groups.find(static_cast<Uint32>(event.get_type()));
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
    }
private:
    HashMap<Uint32, WrappedHandleGroup> m_groups;

    Uint64 m_uid_counter = 1;
};

}

#endif