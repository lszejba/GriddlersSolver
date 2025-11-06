#ifndef MESSAGE
#define MESSAGE

#include <memory>
#include "Enums.hpp"
#include "ISender.hpp"
#include "IReceiver.hpp"

class Message
{
public:
    Message(std::shared_ptr<ISender> sender, std::shared_ptr<IReceiver> receiver, MessageType type);

private:
    std::shared_ptr<ISender> sender;
    std::shared_ptr<IReceiver> receiver;
    MessageType type;
};

#endif
