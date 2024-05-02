#pragma once
#include "StateArrow.h"
#include "../Containers/Vector.h"

class State
{
public:
    State* CheckState();


    void AddArrow(const StateArrow& stateArrow);
    void SetId(int id);
    int GetId() const;

private:
    int _id;
    Dosuha::Vector<StateArrow> _nextStates;
};
