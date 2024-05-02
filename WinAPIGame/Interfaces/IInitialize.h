#pragma once

class IInitialize
{
public:
    IInitialize() = default;
    IInitialize(const IInitialize& other) = default;
    IInitialize(IInitialize&& other) noexcept = default;
    IInitialize& operator=(const IInitialize& other) = default;
    IInitialize& operator=(IInitialize&& other) noexcept = default;
    virtual ~IInitialize() = default;

    virtual void Initialize() = 0;
};
