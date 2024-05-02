#pragma once

class IModifier;

class IModifiable
{
public:
    IModifiable() = default;
    IModifiable(const IModifiable& other) = default;
    IModifiable(IModifiable&& other) noexcept = default;
    IModifiable& operator=(const IModifiable& other) = default;
    IModifiable& operator=(IModifiable&& other) noexcept = default;
    virtual ~IModifiable() = default;

    virtual void SetModifier(IModifier* modifier) = 0;
};
