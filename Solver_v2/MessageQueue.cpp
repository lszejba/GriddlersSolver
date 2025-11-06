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

void MessageQueue::ProcessNotify(std::shared_ptr<ISender> sender, MessageType type)
{
    if (registered.count(sender) == 0)
    {
        return;
    }
    for (auto receiver : registered[sender])
    {
        AddMessage(std::make_shared<Message>(sender, receiver, type));
    }
}

std::vector<std::shared_ptr<IReceiver>>* MessageQueue::GetReceiversForSender(std::shared_ptr<ISender> sender)
{
    if (registered.count(sender) == 0)
    {
        return nullptr;
    }
    return &(registered[sender]);
}

// --- PRIVATE ---

MessageQueue::MessageQueue()
{
}
