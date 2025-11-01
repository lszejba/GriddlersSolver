#ifndef ISENDER
#define ISENDER

class ISender
{
public:
    virtual ~ISender() = default;
    virtual void Notify() = 0;
};

#endif
