#include "Trigger.h"

#include "../../InputComponents/IInputValue.h"

Trigger::Trigger(): _trigger(nullptr)
{
}

Trigger::Trigger(const IInputValue* trigger): _trigger(trigger)
{
}

void Trigger::SetTrigger(IInputValue* trigger)
{
    _trigger = trigger;
}

float Trigger::Invoke() const
{
    return _trigger->GetInputValue();
}
