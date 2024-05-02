#pragma once

class IFinalize
{
public:
    IFinalize() = default;
    IFinalize(const IFinalize& other) = default;
    IFinalize(IFinalize&& other) noexcept = default;
    IFinalize& operator=(const IFinalize& other) = default;
    IFinalize& operator=(IFinalize&& other) noexcept = default;
    virtual ~IFinalize() = default;

    virtual void Finalize() = 0;
};
