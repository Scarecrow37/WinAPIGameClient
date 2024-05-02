#pragma once

class IContain
{
public:
    IContain() = default;
    IContain(const IContain& container) = default;
    IContain& operator=(const IContain& container) = default;
    IContain(IContain&& container) = default;
    IContain& operator=(IContain&& container) = default;
    virtual ~IContain() = default;

    virtual bool Empty() const = 0;
    virtual size_t Size() const = 0;
};
