#include "InputAction.h"

#include <set>

#include "../../../Models/ActionValue/ActionValue.h"
#include "../Invokers/Invoker.h"
#include "../InvokerSet/InvokerSet.h"
#include "../Modifiers/Modifier.h"
#include "../Triggers/Trigger.h"


InputAction::InputAction() : _previousState(false),
                             _currentState(false)
{
}

void InputAction::AddInvokerSet(IInvokerSet* invokerSet)
{
    _sets.PushBack(invokerSet);
}

InputAction::Builder& InputAction::Builder::GetInstance()
{
    static Builder builder;
    return builder;
}

InputAction::Builder& InputAction::Builder::Initialize()
{
    _invokerSet = nullptr;
    _inputAction = new InputAction;
    return *this;
}

InputAction::Builder& InputAction::Builder::OpenInvokerSet()
{
    _invokerSet = new InvokerSet();
    return *this;
}

InputAction::Builder& InputAction::Builder::AddInvoker(const IInputValue* trigger)
{
    Invoker* invoker = new Invoker();
    invoker->SetTrigger(new Trigger(trigger));
    invoker->SetModifier(new Modifier);
    _invokerSet->AddInvoker(invoker);
    return *this;
}

InputAction::Builder& InputAction::Builder::AddInvoker(const IInputValue* trigger, const IAxisModifyStrategy& strategy)
{
    Invoker* invoker = new Invoker();
    invoker->SetTrigger(new Trigger(trigger));
    Modifier* modifier = new Modifier;
    modifier->SetStrategy(strategy);
    invoker->SetModifier(modifier);
    _invokerSet->AddInvoker(invoker);
    return *this;
}

InputAction::Builder& InputAction::Builder::AddInvoker(const IInputValue* trigger,
                                                       const IDirectionModifyStrategy& strategy)
{
    Invoker* invoker = new Invoker();
    invoker->SetTrigger(new Trigger(trigger));
    Modifier* modifier = new Modifier;
    modifier->SetStrategy(strategy);
    invoker->SetModifier(modifier);
    _invokerSet->AddInvoker(invoker);
    return *this;
}

InputAction::Builder& InputAction::Builder::AddInvoker(const IInputValue* trigger,
                                                       const IAxisModifyStrategy& axisStrategy,
                                                       const IDirectionModifyStrategy& directionStrategy)
{
    Invoker* invoker = new Invoker();
    invoker->SetTrigger(new Trigger(trigger));
    Modifier* modifier = new Modifier;
    modifier->SetStrategy(axisStrategy);
    modifier->SetStrategy(directionStrategy);
    invoker->SetModifier(modifier);
    _invokerSet->AddInvoker(invoker);
    return *this;
}

InputAction::Builder& InputAction::Builder::CloseInvokerSet()
{
    _inputAction->AddInvokerSet(_invokerSet);
    _invokerSet = nullptr;
    return *this;
}

InputAction* InputAction::Builder::Build() 
{
    auto inputAction = _inputAction;
    _inputAction = nullptr;
    return inputAction;
}

InputAction::Builder::Builder() : _inputAction(nullptr), _invokerSet(nullptr)
{
}


InputAction::~InputAction()
{
    for (const IInvokerSet* invokerSet : _sets)
    {
        delete invokerSet;
    }
}

void InputAction::Update()
{
    ActionValue value{};
    auto invokerSetIter = _sets.begin();
    while (!(invokerSetIter == _sets.end() || value))
    {
        value = (*invokerSetIter)->GetActionValue();
        ++invokerSetIter;
    }
    _currentState = value;
    if (!_previousState && _currentState)
    {
        for (const auto& effect : _startedEffects)
        {
            std::invoke(effect, value);
        }
    }
    if (_currentState)
    {
        for (const auto& effect : _triggeredEffects)
        {
            std::invoke(effect, value);
        }
    }
    if (_previousState && !_currentState)
    {
        for (const auto& effect : _completedEffects)
        {
            std::invoke(effect, value);
        }
    }
    _previousState = _currentState;
}


