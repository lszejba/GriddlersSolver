#ifndef MESSAGE
#define MESSAGE

#include "ISender.hpp"
#include "IReceiver.hpp"

class Message
{
public:
    Message(ISender sender, IReceiver receiver);

private:
    ISender sender;
    IReceiver receiver;
};

#endif
