#pragma once

class IInputValue;

class ITrigger
{
public:
    ITrigger() = default;
    ITrigger(const ITrigger& other) = default;
    ITrigger(ITrigger&& other) noexcept = default;
    ITrigger& operator=(const ITrigger& other) = default;
    ITrigger& operator=(ITrigger&& other) noexcept = default;
    virtual ~ITrigger() = default;

    virtual void SetTrigger(IInputValue* trigger) = 0;
    virtual float Invoke() const = 0;
};
