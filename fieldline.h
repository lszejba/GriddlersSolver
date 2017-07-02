#ifndef FIELDLINE_H
#define FIELDLINE_H

#include <field.h>
#include <fieldgroup.h>
#include <vector>

class FieldLine
{
public:
    FieldLine(int iSize);
    bool AddField(Field *field, int index);
    void ChangeOccured() { isChanged = true; }
    void Process();
    void AddFieldGroup(FieldGroup group) { iGroups.push_back(group); }
    FieldGroup * GetFieldGroup(int index) { return &iGroups[index]; }
    void PrintSelf(int index);
    void Print();
private:
    int GroupsContainingField(int index);
    std::vector<FieldGroup> iGroups;
    std::vector<Field *> iFields;
    int iSize;
    bool isChanged; // if true, fieldline will process itself
};

#endif // FIELDLINE_H
