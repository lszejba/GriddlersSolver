#include "fieldgroup.h"
#include <iostream>

FieldGroup::FieldGroup(int size) : iSize(size)
{
std::cout << "FieldGroup Constructor(" << size << ")\n";
    iLowerLimit = -1;
    iUpperLimit = -1;
}

int FieldGroup::Range()
{
    if (iLowerLimit < 0 || iUpperLimit < 0)
        return 0;
    return iUpperLimit - iLowerLimit + 1;
}

void FieldGroup::SetLowerLimit(int limit)
{
    std::cout << "SetLowerLimit(" << limit << ") -> " << iLowerLimit << " - " << iUpperLimit << std::endl;
    if (iLowerLimit < 0) {
        iLowerLimit = limit;
        std::cout << "Lower limit set: " << iLowerLimit << std::endl;
        std::cout << "-> SetLowerLimit(" << limit << ") -> " << iLowerLimit << " - " << iUpperLimit << std::endl;
        return;
    }

    if (limit > iUpperLimit && iUpperLimit >= 0) {
        std::cout << "Error: lower limit can't be greater than upper\n";
        return;
    }
    if (limit < iLowerLimit) {
        std::cout << "Error: lower limit cannot be lowered\n";
        return;
    }

    iLowerLimit = limit;
}

void FieldGroup::SetUpperLimit(int limit)
{
    std::cout << "SetUpperLimit(" << limit << ") -> " << iLowerLimit << " - " << iUpperLimit << std::endl;
    if (iUpperLimit < 0) {
        iUpperLimit = limit;
        std::cout << "Upper limit set: " << iUpperLimit << std::endl;
        std::cout << "-> SetUpperLimit(" << limit << ") -> " << iLowerLimit << " - " << iUpperLimit << std::endl;
        return;
    }

    if (limit < iLowerLimit && iLowerLimit >= 0) {
        std::cout << "Error: upper limit can't be smaller than lower\n";
        return;
    }
    if (limit > iUpperLimit) {
        std::cout << "Error: upper limit cannot be raised\n";
        return;
    }

    iUpperLimit = limit;
}

void FieldGroup::PrintSelf()
{
    std::cout << "[" << iSize << " (" << iLowerLimit << " - " << iUpperLimit << ")]";
}

bool FieldGroup::ContainsField(int index)
{
    if (iLowerLimit < 0 || iUpperLimit < 0)
        return false;

    return ((index >= iLowerLimit) && (index <= iUpperLimit));
}
