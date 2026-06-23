#include "pch.h"
#include "event_manager.h"
#include "../backends/sdl/event/sdl_event_adapter.h"
#include "../utils/memory/allocator.h"

namespace yialite
{
EventManager::~EventManager()
{
    DEALLOCATE_OBJECT(IEventAdapter, m_evt_adapter);
}

EventManager::EventManager(EventManager&& other) noexcept
    : m_bus(std::move(other.m_bus))
    , has_devui(other.has_devui)
    , m_evt_adapter(other.m_evt_adapter)
{
    other.m_evt_adapter = nullptr;
    other.has_devui = false;
}

EventManager& EventManager::operator=(EventManager&& other) noexcept
{
    if (this == &other) return *this;
    
    m_bus = std::move(other.m_bus);
    has_devui = other.has_devui;
    DEALLOCATE_OBJECT(IEventAdapter, m_evt_adapter);
    m_evt_adapter = other.m_evt_adapter;
    
    other.m_evt_adapter = nullptr;
    other.has_devui = false;
    return *this;
}

Result<EventManager*> EventManager::create()
{
    EventManager* mgr = ALLOCATE_OBJECT(EventManager);
    if (!mgr) return Result<EventManager*>(ErrorCode::OutOfMemory);

    mgr->m_evt_adapter = ALLOCATE_OBJECT(SDLEventAdapter);
    return mgr;
}

void EventManager::destroy(EventManager* mgr)
{
    DEALLOCATE_OBJECT(EventManager, mgr);
}

void EventManager::set_devui(DevUI* devui)
{
    has_devui = (devui != nullptr);
}

void EventManager::poll_event()
{
    m_evt_adapter->poll_event(m_bus, has_devui);
}

} // namespace yialite
