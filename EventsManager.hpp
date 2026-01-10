#ifndef EVENTS_MANAGER
#define EVENTS_MANAGER

#include <memory>
#include <vector>
#include "Event.hpp"

class EventsManager
{
public:
    static EventsManager& GetInstance();
    void AddEvent(std::shared_ptr<Event> event);

private:
    EventsManager();
    std::vector<std::shared_ptr<Event>> events;
};

#endif
