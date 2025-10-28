#ifndef PHYSICAL_ROW
#define PHYSICAL_ROW

#include <memory>
#include <vector>
#include "Field.hpp"

class PhysicalRow
{
public:
    PhysicalRow(int n, int size);

    void SetField(int n, std::shared_ptr<Field> field);
private:
    int number;
    std::vector<std::shared_ptr<Field>> contents;
};

#endif
