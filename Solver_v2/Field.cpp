#include <iostream>
#include <set>
#include "Field.hpp"

Field::Field(int x, int y) : state(FieldState::Unknown), rowNumber(x), columnNumber(y)
{
}

void Field::Register(LogicalGroup& group)
{
    registeredGroups.insert(&group);
}

void Field::Unregister(LogicalGroup& group)
{
    registeredGroups.erase(&group);
}

void Field::UpdateState(FieldState newState)
{
    if (state != FieldState::Unknown)
    {
        return; // once set, state can't be modified'
    }
    if (newState == FieldState::Unknown)
    {
        return;
    }

    state = newState;
    for (auto logicalGroup : registeredGroups)
    {
        logicalGroup->Process();
    }
}

void Field::Print()
{
    switch(state)
    {
        case FieldState::Unknown:
            std::cout << ".";
            break;
        case FieldState::Empty:
            std::cout << "X";
            break;
        case FieldState::Full:
            std::cout << "#";
            break;
        default:
            std::cout << "?";
            break;
    }
}
