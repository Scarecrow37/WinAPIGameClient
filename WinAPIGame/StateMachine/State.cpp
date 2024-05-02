#include "State.h"

State* State::CheckState()
{
    for (const auto& [changeCondition, pointedState] : _nextStates)
    {
        if (changeCondition()) return pointedState;
    }
    return nullptr;
}

void State::AddArrow(const StateArrow& stateArrow)
{
    _nextStates.PushBack(stateArrow);
}

void State::SetId(const int id)
{
    _id = id;
}

int State::GetId() const
{
    return _id;
}
