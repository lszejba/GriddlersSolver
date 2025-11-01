#include "Message.hpp"

Message::Message(std::shared_ptr<ISender> sender, std::shared_ptr<IReceiver> receiver) : sender(sender), receiver(receiver)
{
}
