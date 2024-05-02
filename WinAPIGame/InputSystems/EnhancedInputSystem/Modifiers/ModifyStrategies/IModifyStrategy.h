#pragma once

union ActionValue;

class IModifyStrategy
{
public:
    IModifyStrategy() = default;
    IModifyStrategy(const IModifyStrategy& other) = default;
    IModifyStrategy(IModifyStrategy&& other) noexcept = default;
    IModifyStrategy& operator=(const IModifyStrategy& other) = default;
    IModifyStrategy& operator=(IModifyStrategy&& other) noexcept = default;
    virtual ~IModifyStrategy() = default;

    virtual void Modify(ActionValue& value) const = 0;
};
