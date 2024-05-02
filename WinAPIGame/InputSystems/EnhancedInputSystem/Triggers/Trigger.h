#pragma once
#include <functional>

#include "ITrigger.h"

class Trigger final : public ITrigger
{
public:
    Trigger();
    explicit Trigger(const IInputValue* trigger);
    void SetTrigger(IInputValue* trigger) override;
    float Invoke() const override;

private:
    const IInputValue* _trigger;
};
