#ifndef FIELD_HPP
#define FIELD_HPP

#include <set>
#include "LogicalGroup.hpp"

class Field
{
public:
    Field(int x, int y);
    void Register(LogicalGroup &);
    void Unregister(LogicalGroup &);

private:
    std::set<LogicalGroup *> registeredGroups;
};

#endif
