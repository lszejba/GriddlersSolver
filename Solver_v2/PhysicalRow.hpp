#ifndef PHYSICAL_ROW
#define PHYSICAL_ROW

#include <memory>
#include <vector>
#include "Field.hpp"
#include "LogicalGroup.hpp"

enum PhysicalRowType
{
    Row,
    Column
};

class PhysicalRow
{
public:
    PhysicalRow(int n, PhysicalRowType type, int size);

    void SetField(int n, std::shared_ptr<Field> field);
    void CreateLogicalGroups(std::vector<int> &logicalGroups);
private:
    int number;
    PhysicalRowType type;
    std::vector<std::shared_ptr<Field>> contents;
    std::vector<std::shared_ptr<LogicalGroup>> groups;
};

#endif
