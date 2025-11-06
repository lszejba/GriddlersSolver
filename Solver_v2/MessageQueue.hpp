#ifndef MESSAGE_QUEUE
#define MESSAGE_QUEUE

#include <map>
#include <memory>
#include <queue>
#include "Message.hpp"

class MessageQueue
{
public:
    static MessageQueue& GetInstance();
    void AddMessage(std::shared_ptr<Message> message);
    void ProcessNotify(std::shared_ptr<ISender>, MessageType type);
    std::vector<std::shared_ptr<IReceiver>>* GetReceiversForSender(std::shared_ptr<ISender> sender);

private:
    MessageQueue();
    std::queue<std::shared_ptr<Message>> messages;
    std::map<std::shared_ptr<ISender>, std::vector<std::shared_ptr<IReceiver>> > registered;
};

#endif
