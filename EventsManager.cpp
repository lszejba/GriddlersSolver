#include "EventsManager.hpp"

EventsManager& EventsManager::GetInstance()
{
    static EventsManager instance;
    return instance;
}

void EventsManager::AddEvent(std::shared_ptr<Event> event)
{
    events.push_back(event);
}

EventsManager::EventsManager()
{
}
