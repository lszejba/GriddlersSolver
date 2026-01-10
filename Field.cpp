#include <iostream>
#include <set>
#include <sstream>
#include "Field.hpp"
#include "MessageQueue.hpp"

Field::Field(int x, int y) : state(FieldState::Unknown), rowNumber(x), columnNumber(y)
{
}

void Field::UpdateState(FieldState newState)
{
    std::cout << "[Field.UPDATESTATE] start" << std::endl;
    if (state != FieldState::Unknown)
    {
        return; // once set, state can't be modified'
    }
    if (newState == FieldState::Unknown)
    {
        return;
    }

    state = newState;
    MessageQueue& mQueue = MessageQueue::GetInstance();

    std::shared_ptr<ISender> thisPtr = shared_from_this();
    std::vector<std::shared_ptr<IReceiver>> receivers = mQueue.GetReceiversForSender(thisPtr);
    for (auto rcvPtr : receivers)
    {
        mQueue.AddMessage(std::make_shared<Message>(thisPtr, rcvPtr, newState == FieldState::Empty ? MessageType::Unregister : MessageType::SenderUpdated));
    }
    std::cout << "[Field.UPDATESTATE] done" << std::endl;
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
    MessageQueue& mQueue = MessageQueue::GetInstance();
    mQueue.ProcessNotify(shared_from_this(), MessageType::SenderUpdated);
}

std::string Field::SenderName()
{
    std::ostringstream oss;
    oss << "Field [" << this->rowNumber << "," << this->columnNumber << "]";
    return oss.str();
}


FieldState Field::GetState()
{
    return state;
}

