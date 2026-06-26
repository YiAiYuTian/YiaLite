#ifndef YIALITE_EVENT_LISTENER_H
#define YIALITE_EVENT_LISTENER_H

#include "event_manager.h"

namespace yialite
{

class EventListener
{
public:
    explicit EventListener(EventManager* mgr) : m_mgr(mgr) {}
    virtual ~EventListener()
    {
        if(m_mgr)
        {
            for(auto& sp : m_sps)
            {
                m_mgr->unsubscribe(sp);
            }
        }
    }

    template<typename Fn>
    Subscription subscribe_auto(EventPriority prio, Fn&& f)
    {
        if(!m_mgr) return Subscription{};

        Subscription sp = m_mgr->subscribe(prio, std::forward<Fn>(f));
        m_sps.push_back(sp);
        return sp;
    }

    template<typename Fn>
    Subscription subscribe_auto(Fn&& f)
    {
        if(!m_mgr) return Subscription{};

        Subscription sp = m_mgr->subscribe(std::forward<Fn>(f));
        m_sps.push_back(sp);
        return sp;
    }

    template<typename Fn>
    Subscription callback_once_auto(EventPriority prio, Fn&& f)
    {
        if(!m_mgr) return Subscription{};

        Subscription sp = m_mgr->callback_once(prio, std::forward<Fn>(f));
        m_sps.push_back(sp);
        return sp;
    }

    template<typename Fn>
    Subscription callback_once_auto(Fn&& f)
    {
        if(!m_mgr) return Subscription{};

        Subscription sp = m_mgr->callback_once(std::forward<Fn>(f));
        m_sps.push_back(sp);
        return sp;
    }

    void unsubscribe_auto(Subscription sp)
    {
        if(!m_mgr) return;

        m_mgr->unsubscribe(sp);

        for (auto it = m_sps.begin(); it != m_sps.end();)
        {
            if (it->callback_id == sp.callback_id)
            {
                m_sps.erase(it);
                break;
            }
            ++it;
        }
    }
private:
    List<Subscription> m_sps;
    EventManager* m_mgr = nullptr;
};

}

#endif