#pragma once

union ActionValue;

class IEnhancedInputObject
{
public:
    IEnhancedInputObject() = default;
    IEnhancedInputObject(const IEnhancedInputObject& other) = default;
    IEnhancedInputObject(IEnhancedInputObject&& other) noexcept = default;
    IEnhancedInputObject& operator=(const IEnhancedInputObject& other) = default;
    IEnhancedInputObject& operator=(IEnhancedInputObject&& other) noexcept = default;
    virtual ~IEnhancedInputObject() = default;
};
