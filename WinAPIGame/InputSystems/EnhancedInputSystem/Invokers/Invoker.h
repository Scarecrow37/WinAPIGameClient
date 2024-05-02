#pragma once
#include "IInvoker.h"
#include "../IActionValue.h"
#include "../IModifiable.h"
#include "../ITriggerable.h"

class Invoker final : public IInvoker
{
public:
    Invoker(const Invoker& other) = default;
    Invoker(Invoker&& other) noexcept = default;
    Invoker& operator=(const Invoker& other) = default;
    Invoker& operator=(Invoker&& other) noexcept = default;
    ~Invoker() override;

    Invoker();
    void SetTrigger(ITrigger* trigger) override;
    void SetModifier(IModifier* modifier) override;
    ActionValue GetActionValue() const override;

private:
    ITrigger* _trigger;
    IModifier* _modifier;
};
