#ifndef FIELD_HPP
#define FIELD_HPP

#include <set>
#include <memory>
#include "Enums.hpp"
#include "ISender.hpp"

class Field : public ISender, public std::enable_shared_from_this<Field>
{
public:
    Field(int x, int y);
    void UpdateState(FieldState newState);
    void Print();
    void Notify();
    std::string SenderName();
    FieldState GetState();

private:
    FieldState state;
    int rowNumber;
    int columnNumber;
};

#endif
