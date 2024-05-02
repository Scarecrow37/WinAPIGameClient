#pragma once

class IInputValue
{
public:
    IInputValue() = default;
    IInputValue(const IInputValue& other) = default;
    IInputValue(IInputValue&& other) noexcept = default;
    IInputValue& operator=(const IInputValue& other) = default;
    IInputValue& operator=(IInputValue&& other) noexcept = default;
    virtual ~IInputValue() = default;

    virtual float GetInputValue() const = 0;
};
