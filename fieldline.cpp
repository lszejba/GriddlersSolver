#include "fieldline.h"
#include <iostream>

FieldLine::FieldLine(int size, std::string type, int index) : iSize(size), iType(type), iIndex(index),  isChanged(true)
{
    iFields = std::vector<Field *>(size);
    for (int i = 0; i < size; i++)
        iFields[i] = nullptr;
}

bool FieldLine::AddField(Field *field, int index)
{
    if (field == nullptr) {
        std::cout << "Field can't be null\n";
        return false;
    }
    if (index < 0 || index >= iSize) {
        std::cout << "Invalid index\n";
        return false;
    }
    if (iFields[index] != nullptr) {
        std::cout << "Field with this index has already been set\n";
        return false;
    }
    iFields[index] = field;
    return true;
}

void FieldLine::Process()
{
//    if (!isChanged)
//        return;
    isChanged = false;

    int longestGroupSize = 0;
    // Actions to do:
    // 1. Adjust group limits - according to fields set by other fieldLines
    for (auto it = iGroups.begin(); it != iGroups.end(); it++) {
        if ((*it).Size() > longestGroupSize)
            longestGroupSize = (*it).Size();
        if ((*it).IsComplete())
            continue;
        std::vector<int> fullFields; // full fields belonging to this group exclusively
        for (int i = (*it).LowerLimit(); i <= (*it).UpperLimit(); i++) {
            int fieldOwners = 0;
            switch(iFields[i]->GetState()) {
            case State_Empty:
                // TODO: currently unsupported - group size is 2:
                // group looks like this: |  X X  | - middle gap should be set to empty
                if (i - (*it).LowerLimit() < (*it).Size()) // move lower limit
                    (*it).SetLowerLimit(i + 1);
                if ((*it).UpperLimit() - i < (*it).Size()) // move upper limit
                    (*it).SetUpperLimit(i - 1);
                break;
            case State_Full:
                fieldOwners = GroupsContainingField(i);
                if (fieldOwners > 1) // leave it be for now
                    break;
                fullFields.push_back(i);
                break;
            case State_Unknown:
                break;
            default:
                break;
            }
        }
        if (fullFields.size() > 0) {
            int minIndex = fullFields[0];
            int maxIndex = fullFields[fullFields.size() - 1];
            for (int j = minIndex; j < maxIndex; j++) // fill the gaps with full fields
                iFields[j]->SetState(State_Full);
            // Recalculate fieldGroup limits
            int missingFields = (*it).Size() - (maxIndex - minIndex + 1);
            if (minIndex - missingFields >= (*it).LowerLimit())
                (*it).SetLowerLimit(minIndex - missingFields);
            if (maxIndex + missingFields <= (*it).UpperLimit())
                (*it).SetUpperLimit(maxIndex + missingFields);
        }
    }

    // 2. Fill gaps between groups with empty fields - fieldLine level
    for (int i = 0; i < iSize; i++) {
        int fieldOwners = GroupsContainingField(i);
        if (fieldOwners == 0)
            iFields[i]->SetState(State_Empty);
    }
    // 3. Check existing groups of full fields:
    std::vector<int> fullFieldGroupIndex;
    std::vector<int> fullFieldGroupSize;
    int currentGroupIndex = -1, currentGroupSize = 0;
    for (int i = 0; i < iSize; i++) {
        if (iFields[i]->GetState() == State_Full) {
            if (currentGroupIndex < 0)
                currentGroupIndex = i;
            currentGroupSize++;
        }
        else {
            if (currentGroupSize > 0) {
                fullFieldGroupIndex.push_back(currentGroupIndex);
                fullFieldGroupSize.push_back(currentGroupSize);
                currentGroupIndex = -1;
                currentGroupSize = 0;
            }
        }
    }
    // 3.1. Limit groups of full fields of length equal to those of longest fieldGroup
    for (int i = 0; i < fullFieldGroupSize.size(); i++) {
        if (fullFieldGroupSize[i] == longestGroupSize) {
            if (fullFieldGroupIndex[i] - 1 > 0)
                iFields[fullFieldGroupIndex[i] - 1]->SetState(State_Empty);
            if (fullFieldGroupIndex[i] + fullFieldGroupSize[i] < iSize)
                iFields[fullFieldGroupIndex[i] + fullFieldGroupSize[i] ]->SetState(State_Empty);
        }
    }
    // 3a. If any of them has max size for fieldLine (according to non-complete fieldGroups)
    //     limit them with empty fields on one or both sides
    // 3b. If 2 (or more) non-complete fieldGroups overlap, and overlapping area contains
    //     groups of full fields of the same size (which is also the size of fieldGroups)
    //     arbitrarly change limits of these fieldGroups to contain one of field groups each
    // TODO: Add processing here
    for (auto it = iGroups.begin(); it != iGroups.end(); it++) {
//        if ((*it).IsComplete())
//            continue;
        // 1. (initial) mark obvious fields
        if ((*it).Range() < 2 * (*it).Size()) {
            for (int i = ((*it).UpperLimit() - (*it).Size() + 1); i < ((*it).LowerLimit() + (*it).Size()); i++) {
                iFields[i]->SetState(State_Full);
            }
        }
    }
}

void FieldLine::PrintSelf() {
    std::cout << "[" << iType << " " << iIndex << "] ";
    for (unsigned i = 0; i < iGroups.size(); i++) {
        iGroups[i].PrintSelf();
        std::cout << " ";
    }
    std::cout << std::endl;
}

void FieldLine::Print()
{
    std::cout << "|";
    for (int i = 0; i < iSize; i++) {
        iFields[i]->Print();
    }
    std::cout << "|\n";
}

int FieldLine::GroupsContainingField(int index)
{
    int count = 0;
    for (auto it = iGroups.begin(); it != iGroups.end(); it++) {
        if ((*it).ContainsField(index))
            count++;
    }

    return count;
}
