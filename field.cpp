#include "field.h"
#include "fieldline.h"
#include <iostream>

Field::Field() : iState(State_Unknown)
{
    iParents[0] = iParents[1] = nullptr;
}

void Field::AddParent(FieldLine *parent)
{
    if (parent == nullptr) {
        std::cout << "Parent is null\n";
        return;
    }
    if (iParents[0] == nullptr) {
        iParents[0] = parent;
        return;
    }
    if (iParents[1] == nullptr) {
        iParents[1] = parent;
        return;
    }
    std::cout << "All parents are set\n";
}

void Field::SetState(FieldState newState)
{
//    std::cout << "SetState()" << std::endl;
    if (iState == newState) // don't trigger ChangeOccured if there is none
        return;
    iState = newState;
    if (iParents[0] != nullptr)
        iParents[0]->ChangeOccured();
    if (iParents[1] != nullptr)
        iParents[1]->ChangeOccured();
}

void Field::Print()
{
    switch (iState) {
    case State_Empty:
        std::cout << "-";
        break;
    case State_Full:
        std::cout << "#";
        break;
    case State_Unknown:
    default:
        std::cout << " ";
    }
}
