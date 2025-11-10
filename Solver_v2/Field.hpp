#ifndef FIELD_HPP
#define FIELD_HPP

#include <set>
#include "Enums.hpp"
#include "ISender.hpp"

class Field : public ISender
{
public:
    Field(int x, int y);
    void UpdateState(FieldState newState);
    void Print();
    void Notify();
    std::string SenderName();

private:
    FieldState state;
    int rowNumber;
    int columnNumber;
};

#endif
