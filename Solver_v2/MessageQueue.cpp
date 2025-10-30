#include "MessageQueue.hpp"

MessageQueue& MessageQueue::GetInstance()
{
    static MessageQueue instance;
    return instance;
}
