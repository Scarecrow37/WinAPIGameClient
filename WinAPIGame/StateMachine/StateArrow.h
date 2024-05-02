#pragma once
#include <functional>

class State;

struct StateArrow
{
    std::function<bool()> changeCondition;
    State* pointedState;
};
