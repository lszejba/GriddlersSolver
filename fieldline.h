#ifndef FIELDLINE_H
#define FIELDLINE_H

#include <field.h>
#include <fieldgroup.h>
#include <vector>
#include <string>

class FieldLine
{
public:
    FieldLine(int size, std::string type, int index);
    bool AddField(Field *field, int index);
    void ChangeOccured() { isChanged = true; }
    bool Process();
    void AddFieldGroup(FieldGroup group) { iGroups.push_back(group); }
    FieldGroup * GetFieldGroup(int index) { return &iGroups[index]; }
    void PrintSelf();
    void Print();
    int NumberOfGroups() { return iGroups.size(); }
    int GroupSize(int index) { (index >= 0 && index < iGroups.size()) ? iGroups[index].Size() : 0; }
private:
    std::vector<int> GroupsContainingField(int index);
    std::vector<FieldGroup> iGroups;
    std::vector<Field *> iFields;
    int iSize;
    std::string iType;
    int iIndex;
    bool isChanged; // if true, fieldline will process itself
};

#endif // FIELDLINE_H
