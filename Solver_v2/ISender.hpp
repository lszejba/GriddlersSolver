#ifndef ISENDER
#define ISENDER

class ISender
{
public:
    virtual ~ISender() = default;
    virtual void Notify() = 0;
    virtual std::string SenderName() = 0;
};

#endif
