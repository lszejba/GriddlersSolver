#include "Message.hpp"

Message::Message(std::shared_ptr<ISender> sender, std::shared_ptr<IReceiver> receiver, MessageType type) : sender(sender), receiver(receiver), type(type)
{
}

MessageType Message::GetType()
{
    return type;
}

std::shared_ptr<ISender> Message::GetSender()
{
    return sender;
}

std::shared_ptr<IReceiver> Message::GetReceiver()
{
    return receiver;
}
