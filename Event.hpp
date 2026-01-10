#ifndef EVENT
#define EVENT

#include "Enums.hpp"

class Event
{
public:
    Event(int x, int y, FieldState s);

private:
    int row;
    int column;
    FieldState state;
};

#endif
