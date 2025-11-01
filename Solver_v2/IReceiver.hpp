#ifndef IRECEIVER
#define IRECEIVER

class IReceiver
{
public:
    virtual ~IReceiver() = default;
    virtual void Register() = 0;
    virtual void UnRegister() = 0;
};

#endif
