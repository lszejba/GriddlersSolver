#ifndef FIELD_H
#define FIELD_H

class FieldLine;

enum FieldState {
    State_Unknown 	= -1,
    State_Empty		= 0,
    State_Full		= 1
};

class Field
{
public:
    Field();
    void AddParent(FieldLine *parent);
    void SetState(FieldState newState);
    FieldState GetState() {return iState; }
    void Print();
private:
    FieldState iState;
    FieldLine *iParents[2];
};

#endif // FIELD_H
