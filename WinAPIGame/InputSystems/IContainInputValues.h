#pragma once

class IInputValue;

class IContainInputValues
{
public:
    IContainInputValues() = default;
    IContainInputValues(const IContainInputValues& other) = default;
    IContainInputValues(IContainInputValues&& other) noexcept = default;
    IContainInputValues& operator=(const IContainInputValues& other) = default;
    IContainInputValues& operator=(IContainInputValues&& other) noexcept = default;
    virtual ~IContainInputValues() = default;

    virtual const IInputValue* GetInputValueGetter(unsigned char componentCode) const = 0 ;
};
