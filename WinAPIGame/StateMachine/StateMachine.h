#pragma once
#include <functional>

#include "../Interfaces/IUpdate.h"

class State;

class StateMachine : public IUpdate
{
public:
    StateMachine(State* beginState);
    void Update() override;
    State* GetCurrentState() const;
    void BindOnStateChanged(const std::function<void()>& function);

private:
    State* _currentState;
    std::function<void()> _onStateChanged;
};
