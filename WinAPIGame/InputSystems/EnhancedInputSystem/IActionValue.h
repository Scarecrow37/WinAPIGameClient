#pragma once
#include "../../Models/ActionValue/ActionValue.h"

class IActionValue
{
public:
    IActionValue() = default;
    IActionValue(const IActionValue& other) = default;
    IActionValue(IActionValue&& other) noexcept = default;
    IActionValue& operator=(const IActionValue& other) = default;
    IActionValue& operator=(IActionValue&& other) noexcept = default;
    virtual ~IActionValue() = default;

    virtual ActionValue GetActionValue() const = 0;
};
