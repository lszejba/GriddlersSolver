#ifndef FIELDGROUP_H
#define FIELDGROUP_H

#include <vector>
#include <field.h>

class FieldGroup
{
public:
    FieldGroup(int size);
    int Size() { return iSize; }
    int Range();
    int LowerLimit() { return iLowerLimit; }
    int UpperLimit() { return iUpperLimit; }
    void SetLowerLimit(int limit);
    void SetUpperLimit(int limit);
    bool IsComplete() { return ((iUpperLimit - iLowerLimit + 1) == iSize) || (iSize == 0); }
    void PrintSelf();
    bool ContainsField(int index);
protected:
    int iSize;
    int iLowerLimit;
    int iUpperLimit;
};

#endif // FIELDGROUP_H
