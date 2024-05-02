#include "StateMachine.h"

#include "State.h"

StateMachine::StateMachine(State* beginState): _currentState(beginState)
{
}

void StateMachine::Update()
{
    if (State* state = _currentState->CheckState())
    {
        _currentState = state;
        _onStateChanged();
    }
}

State* StateMachine::GetCurrentState() const
{
    return _currentState;
}

void StateMachine::BindOnStateChanged(const std::function<void()>& function)
{
    _onStateChanged = function;
}
