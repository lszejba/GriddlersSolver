#include <algorithm>
#include <iostream>
#include "IReceiver.hpp"
#include "MessageQueue.hpp"

MessageQueue& MessageQueue::GetInstance()
{
    static MessageQueue instance;
    return instance;
}

void MessageQueue::AddMessage(std::shared_ptr<Message> message)
{
    std::shared_ptr<ISender> sender = message->GetSender();
    std::shared_ptr<IReceiver> receiver = message->GetReceiver();
    switch (message->GetType())
    {
        case MessageType::Register:
            if (registered.count(sender) == 0)
            {
                registered[sender] = std::vector<std::shared_ptr<IReceiver>>();
            }
            registered[sender].push_back(receiver);
            std::cout << "[Register] " << receiver->ReceiverName() << " registered to " << sender->SenderName() << std::endl;
            break;
        case MessageType::Unregister:
            if (registered.count(sender) == 0)
            {
                return;
            }
            registered[sender].erase(std::remove(registered[sender].begin(), registered[sender].end(), receiver), registered[sender].end());
            std::cout << "[Unregister] " << receiver->ReceiverName() << " unregistered from " << sender->SenderName() << std::endl;
            break;
        case MessageType::SenderUpdated:
        default:
            break;
    }
    // One message at a time per IReceiver
    bool rcvFound = false;
    for (auto& msg : messages)
    {
        if (msg->GetReceiver().get() == receiver.get())
        {
            rcvFound = true;
            break;
        }
    }
    if (!rcvFound)
    {
        messages.push_back(message);
    }
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

std::shared_ptr<Message> MessageQueue::GetNextMessage()
{
    if (messages.empty())
    {
        return nullptr;
    }
    std::shared_ptr<Message> result = messages.front();
    messages.pop_front();

    return result;
}


// --- PRIVATE ---

MessageQueue::MessageQueue()
{
}
