#ifndef IRECEIVER
#define IRECEIVER

class IReceiver
{
public:
    virtual ~IReceiver() = default;
    virtual void Process() = 0;
    virtual std::string ReceiverName() = 0;
};

#endif
