#include "PhysicalRow.hpp"

PhysicalRow::PhysicalRow(int n, PhysicalRowType type, int size) : number(n), type(type)
{
    contents.reserve(size);
}

void PhysicalRow::SetField(int n, std::shared_ptr<Field> field)
{
    contents[n] = field;
}

void PhysicalRow::CreateLogicalGroups(std::vector<int>& logicalGroups)
{
    groups.reserve(logicalGroups.size());
    for (unsigned int i = 0; i < logicalGroups.size(); i++)
    {
        groups[i] = std::make_shared<LogicalGroup>(logicalGroups[i]);
    }
}
