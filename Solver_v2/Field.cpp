#include <set>
#include "Field.hpp"

void Field::Register(LogicalGroup& group)
{
    registeredGroups.insert(&group);
}

void Field::Unregister(LogicalGroup& group)
{
    registeredGroups.erase(&group);
}
