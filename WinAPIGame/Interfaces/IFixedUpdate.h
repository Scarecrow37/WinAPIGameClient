#pragma once

class IFixedUpdate
{
public:
    IFixedUpdate() = default;
    IFixedUpdate(const IFixedUpdate& other) = default;
    IFixedUpdate(IFixedUpdate&& other) noexcept = default;
    IFixedUpdate& operator=(const IFixedUpdate& other) = default;
    IFixedUpdate& operator=(IFixedUpdate&& other) noexcept = default;
    virtual ~IFixedUpdate() = default;

    virtual void FixedUpdate() = 0;
};
