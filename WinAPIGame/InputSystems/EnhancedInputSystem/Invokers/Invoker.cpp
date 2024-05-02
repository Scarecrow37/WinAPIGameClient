#include "Invoker.h"

#include "../Modifiers/IModifier.h"
#include "../Triggers/ITrigger.h"

Invoker::~Invoker()
{
    delete _trigger;
    delete _modifier;
}

Invoker::Invoker(): _trigger(nullptr), _modifier(nullptr)
{
}

void Invoker::SetTrigger(ITrigger* trigger)
{
    _trigger = trigger;
}

void Invoker::SetModifier(IModifier* modifier)
{
    _modifier = modifier;
}

ActionValue Invoker::GetActionValue() const
{
    ActionValue value{};
    value.scalar = _trigger->Invoke();
    _modifier->Modify(value);
    return value;
}
