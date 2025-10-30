#ifndef MESSAGE_QUEUE
#define MESSAGE_QUEUE

#include <memory>
#include <queue>
#include "Message.hpp"

class MessageQueue
{
public:
    static MessageQueue& GetInstance();
    void AddMessage(std::shared_ptr<Message> message);

private:
    MessageQueue();
    std::queue<Message> messages;
};

#endif
