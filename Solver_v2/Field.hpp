#ifndef FIELD_HPP
#define FIELD_HPP

#include <set>
//#include "LogicalGroup.hpp"

enum FieldState
{
    Unknown = -1,
    Empty = 0,
    Full = 1
};

class Field
{
public:
    Field(int x, int y);
    //void Register(LogicalGroup &);
    //void Unregister(LogicalGroup &);
    void UpdateState(FieldState newState);
    void Print();

private:
    //std::set<LogicalGroup *> registeredGroups;
    FieldState state;
    int rowNumber;
    int columnNumber;
};

#endif
