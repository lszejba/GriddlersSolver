#include "Message.hpp"

Message::Message(ISender sender, IReceiver receiver) : sender(sender), receiver(receiver)
{
}
