#include "Message.hpp"

Message::Message(std::shared_ptr<ISender> sender, std::shared_ptr<IReceiver> receiver, MessageType type) : sender(sender), receiver(receiver), type(type)
{
}
