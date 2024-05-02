#pragma once

class ITrigger;

class ITriggerable
{
public:
    ITriggerable() = default;
    ITriggerable(const ITriggerable& other) = default;
    ITriggerable(ITriggerable&& other) noexcept = default;
    ITriggerable& operator=(const ITriggerable& other) = default;
    ITriggerable& operator=(ITriggerable&& other) noexcept = default;
    virtual ~ITriggerable() = default;

    virtual void SetTrigger(ITrigger* trigger) = 0;
};
