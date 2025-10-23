#ifndef PHYSICAL_ROW
#define PHYSICAL_ROW

#include <vector>
#include "Field.hpp"

class PhysicalRow
{
public:

private:
    int number;
    std::vector<Field *> contents;
};

#endif
