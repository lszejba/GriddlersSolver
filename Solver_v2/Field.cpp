#include <iostream>
#include <set>
#include "Field.hpp"
#include "MessageQueue.hpp"

Field::Field(int x, int y) : state(FieldState::Unknown), rowNumber(x), columnNumber(y)
{
}

/*void Field::Register(LogicalGroup& group)
{
    registeredGroups.insert(&group);
}*/

/*void Field::Unregister(LogicalGroup& group)
{
    registeredGroups.erase(&group);
}*/

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
    // TODO: send info to MessageQueue to run Process on all IReceivers registered to this Field
    /*for (auto logicalGroup : registeredGroups)
    {
        logicalGroup->Process();
    }*/
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

void Field::Notify()
{
    MessageQueue mQueue = MessageQueue::GetInstance();
    mQueue.ProcessNotify(std::shared_ptr<ISender>(this), MessageType::SenderUpdated);
}

