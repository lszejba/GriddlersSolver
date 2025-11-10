#include <sstream>
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
    if (logicalGroups.size() < 1 || (logicalGroups.size() == 1 && logicalGroups[0] == 0))
    {
        groups.clear();
    }
    groups.reserve(logicalGroups.size());
    for (unsigned int i = 0; i < logicalGroups.size(); i++)
    {
        groups[i] = std::make_shared<LogicalGroup>(logicalGroups[i]);
    }
}

void PhysicalRow::Process()
{

}

std::string PhysicalRow::ReceiverName()
{
    std::ostringstream oss;
    oss << "PhysicalRow (" << ((type == PhysicalRowType::Row) ? "Row" : "Column") << ") [" << this->number << "]";
    return oss.str();
}
