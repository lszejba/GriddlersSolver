#include "fieldline.h"
#include <iostream>

#ifdef LOG
void FieldLine::log(std::string info)
{
    std::cout << "[" << iID << "] " << info << std::endl;
}

void FieldLine::log(std::string info, int value)
{
    std::cout << "[" << iID << "] " << info << "(value: " << value << ")" << std::endl;
}
#endif
#ifndef LOG
void FieldLine::log(std::string) {}
void FieldLine::log(std::string, int) {}
#endif

FieldLine::FieldLine(int size, std::string type, int index) : iSize(size), iID(type + std::to_string(index)), isChanged(true)
{
    iFields = std::vector<Field *>(size);
    for (int i = 0; i < size; i++)
        iFields[i] = nullptr;
}

bool FieldLine::AddField(Field *field, int index)
{
    if (field == nullptr) {
        log("Field can't be null");
        return false;
    }
    if (index < 0 || index >= iSize) {
        log("Invalid index");
        return false;
    }
    if (iFields[index] != nullptr) {
        log("Field with this index has already been set");
        return false;
    }
    iFields[index] = field;
    return true;
}

bool FieldLine::Process()
{
    log("Inside process");
//    if (!isChanged)
//        return isChanged;
    isChanged = false;

    int longestGroupSize = 0;
    // Actions to do:
    // 1. Adjust group limits - according to fields set by other fieldLines
    for (auto it = iGroups.begin(); it != iGroups.end(); it++) {
        if ((*it).IsComplete())
            continue;
        std::vector<int> fullFields; // full fields belonging to this group exclusively
        for (int i = (*it).LowerLimit(); i <= (*it).UpperLimit(); i++) {
            std::vector<int> fieldOwners;
            switch(iFields[i]->GetState()) {
            case State_Empty:
                // TODO: currently unsupported - group size is 2:
                // group looks like this: |  X X  | - middle gap should be set to empty
                if (i - (*it).LowerLimit() < (*it).Size()) { // move lower limit
                    (*it).SetLowerLimit(i + 1);
                    log("Move lower limit", i + 1);
                }
                if ((*it).UpperLimit() - i < (*it).Size()) { // move upper limit
                    (*it).SetUpperLimit(i - 1);
                    log("Move upper limit", i - 1);
                }
                break;
            case State_Full:
                fieldOwners = GroupsContainingField(i);
                if (fieldOwners.size() > 1) // leave it be for now
                    break;
                fullFields.push_back(i);
                break;
            case State_Unknown:
                break;
            default:
                break;
            }
        }
        log("Full fields size: ", fullFields.size());
        if (fullFields.size() > 0) {
            int minIndex = fullFields[0];
            int maxIndex = fullFields[fullFields.size() - 1];
            for (int j = minIndex; j < maxIndex; j++) { // fill the gaps with full fields
                iFields[j]->SetState(State_Full);
                log("Set field to FULL", j);
            }
            // Recalculate fieldGroup limits
            int missingFields = (*it).Size() - (maxIndex - minIndex + 1);
            if (minIndex - missingFields >= (*it).LowerLimit()) {
                (*it).SetLowerLimit(minIndex - missingFields);
                log("Move lower limit (after fill)", minIndex - missingFields);
            }
            if (maxIndex + missingFields <= (*it).UpperLimit()) {
                (*it).SetUpperLimit(maxIndex + missingFields);
                log("Move upper limit (after fill)", maxIndex + missingFields);
            }
        }
        // mark obvious fields
        if ((*it).Range() < 2 * (*it).Size()) {
            for (int i = ((*it).UpperLimit() - (*it).Size() + 1); i < ((*it).LowerLimit() + (*it).Size()); i++) {
                iFields[i]->SetState(State_Full);
                log("Set obvious field to FULL", i);
            }
        }
    }
    for (auto it = iGroups.begin(); it != iGroups.end(); it++) {
        if ((*it).Size() > longestGroupSize)
            longestGroupSize = (*it).Size();
    }

    // 2. Fill gaps between groups with empty fields - fieldLine level
    FillGapsBetweenGroups();
//    for (int i = 0; i < iSize; i++) {
//        std::vector<int> fieldOwners = GroupsContainingField(i);
//        if (fieldOwners.size() == 0) {
//            iFields[i]->SetState(State_Empty);
//            log("Set field to EMPTY", i);
//        }
//    }
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
    for (unsigned i = 0; i < fullFieldGroupSize.size(); i++) {
        if (fullFieldGroupSize[i] == longestGroupSize) {
            if (fullFieldGroupIndex[i] - 1 > 0) {
                iFields[fullFieldGroupIndex[i] - 1]->SetState(State_Empty);
                log("Set field to EMPTY (lower limit, full group)", fullFieldGroupIndex[i] - 1);
            }
            if (fullFieldGroupIndex[i] + fullFieldGroupSize[i] < iSize) {
                iFields[fullFieldGroupIndex[i] + fullFieldGroupSize[i] ]->SetState(State_Empty);
                log("Set field to EMPTY (upper limit, full group)", fullFieldGroupIndex[i] + fullFieldGroupSize[i]);
            }
        }
        // Check if fieldGroup limits shouldn't be changed due to field of groups being too long
        // or
        // Change limits if fieldGroup contains only part of group of full fields
        std::vector<int> firstFieldOwners = GroupsContainingField(fullFieldGroupIndex[i]);
        std::vector<int> lastFieldOwners = GroupsContainingField(fullFieldGroupIndex[i] + fullFieldGroupSize[i] - 1);
        if (firstFieldOwners.size() != lastFieldOwners.size()) { // remove fieldGroups absent from any of above groups
            // We assume that these groups won't differ very much (bigger group contains all of elements of smaller)
            // Check only limiting elements and change their limits if needed
            if (firstFieldOwners.size() > lastFieldOwners.size()) {
                if (firstFieldOwners[0] != lastFieldOwners[0]) { // first one is odd one
                    int newLimit = fullFieldGroupIndex[i] - 2;
                    if (newLimit > 0) {
                        iGroups[firstFieldOwners[0]].SetUpperLimit(newLimit);
                        log("Set upper limit (group too long)", newLimit);
                    }
                }
                if (firstFieldOwners[firstFieldOwners.size() - 1] != lastFieldOwners[lastFieldOwners.size() - 1]) { // last one is odd one
                    int newLimit = fullFieldGroupIndex[i] + fullFieldGroupSize[i] - 1 + 2;
                    if (newLimit < iSize) {
                        iGroups[firstFieldOwners[firstFieldOwners.size() - 1]].SetLowerLimit(newLimit);
                        log("Set lower limit (group too long)", newLimit);
                    }
                }
            } else {
                if (lastFieldOwners[0] != firstFieldOwners[0]) { // first one is odd one
                    int newLimit = fullFieldGroupIndex[i] - 2;
                    if (newLimit > 0) {
                        iGroups[lastFieldOwners[0]].SetUpperLimit(newLimit);
                        log("Set upper limit (group too long [2]", newLimit);
                    }
                }
                if (lastFieldOwners[lastFieldOwners.size() - 1] != firstFieldOwners[firstFieldOwners.size() - 1]) { // last one is odd one
                    int newLimit = fullFieldGroupIndex[i] + fullFieldGroupSize[i] - 1 + 2;
                    if (newLimit < iSize) {
                        iGroups[lastFieldOwners[firstFieldOwners.size() - 1]].SetLowerLimit(newLimit);
                        log("Set lower limit (group too long [2]", newLimit);
                    }
                }
            }
            isChanged = true;
        } else {
            // we only check first and last fieldGroup, as choosing which limit needs to be
            // changed is easy then.
            if (iGroups[firstFieldOwners[0]].Size() < fullFieldGroupSize[i]) {
                int newLimit = fullFieldGroupIndex[i] - 2;
                if (newLimit > 0) {
                    iGroups[firstFieldOwners[0]].SetUpperLimit(newLimit);
                    log("Set upper limit (remove first group)", newLimit);
                }
                isChanged = true;
            }
            if (iGroups[firstFieldOwners[firstFieldOwners.size() - 1]].Size() < fullFieldGroupSize[i]) {
                int newLimit = fullFieldGroupIndex[i] + fullFieldGroupSize[i] - 1 + 2;
                if (newLimit < iSize) {
                    iGroups[firstFieldOwners[firstFieldOwners.size() - 1]].SetLowerLimit(newLimit);
                    log("Set lower limit (remove last group)", newLimit);
                }
                isChanged = true;
            }
        }
    }
    // 3b. If 2 (or more) non-complete fieldGroups overlap, and overlapping area contains
    //     groups of full fields of the same size (which is also the size of fieldGroups)
    //     arbitrarly change limits of these fieldGroups to contain one of field groups each

    // 4. Modify limits of groups neighbouring with completed groups
    if (iGroups.size() > 1) {
        for (unsigned i = 0; i < iGroups.size(); i++) {
            if (iGroups[i].IsComplete()) {
                if (i > 0) { // check previous group
                    if (iGroups[i - 1].UpperLimit() > (iGroups[i].LowerLimit() - 1)) {
                        iGroups[i - 1].SetUpperLimit(iGroups[i].LowerLimit() - 1);
                        log("Set lower limit (neighbouring complete group", iGroups[i].LowerLimit() - 1);
                    }
                }
                if (i + 1 < iGroups.size()) { // check next group
                    if (iGroups[i + 1].LowerLimit() < (iGroups[i].UpperLimit() + 1)) {
                        iGroups[i + 1].SetLowerLimit(iGroups[i].UpperLimit() + 1);
                        log("Set upper limit (neighbouring complete group", iGroups[i].UpperLimit() + 1);
                    }
                }
            }
        }
    }
    return isChanged;
}

void FieldLine::PrintSelf() {
    std::cout << "[" << iID << "] ";
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

std::vector<int> FieldLine::GroupsContainingField(int index)
{
    std::vector<int> result;
    for (unsigned i = 0; i < iGroups.size(); i++) {
        if (iGroups[i].ContainsField(index))
            result.push_back(i);
    }

    return result;
}

void FieldLine::FillGapsBetweenGroups()
{
    for (int i = 0; i < iSize; i++) {
        if (iFields[i]->GetState() != State_Unknown)
            continue;
        std::vector<int> fieldOwners = GroupsContainingField(i);
        if (fieldOwners.size() == 0) {
            iFields[i]->SetState(State_Empty);
            log("Set field to EMPTY", i);
        }
    }
}
