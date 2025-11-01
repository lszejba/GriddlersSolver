#include "MessageQueue.hpp"

MessageQueue& MessageQueue::GetInstance()
{
    static MessageQueue instance;
    return instance;
}

void MessageQueue::AddMessage(std::shared_ptr<Message> message)
{
    messages.push(message);
}

MessageQueue::MessageQueue()
{
}
