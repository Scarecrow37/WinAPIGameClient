#pragma once

template <typename T>
class ITopAccess
{
public:
    ITopAccess() = default;
    ITopAccess(const ITopAccess& oneWayAccess) = default;
    ITopAccess& operator=(const ITopAccess& oneWayAccess) = default;
    ITopAccess(ITopAccess&& oneWayAccess) = default;
    ITopAccess& operator=(ITopAccess&& oneWayAccess) = default;
    virtual ~ITopAccess() = default;

    virtual T& Top() = 0;
    virtual const T& Top() const = 0;
};
