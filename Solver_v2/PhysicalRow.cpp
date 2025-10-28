#include "PhysicalRow.hpp"

PhysicalRow::PhysicalRow(int n, int size) : number(n)
{
    contents.reserve(size);
}

void PhysicalRow::SetField(int n, std::shared_ptr<Field> field)
{
    contents[n] = field;
}

