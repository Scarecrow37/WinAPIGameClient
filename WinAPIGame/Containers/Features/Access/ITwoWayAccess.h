#pragma once

template <typename T>
class ITwoWayAccess
{
public:
    ITwoWayAccess() = default;
    ITwoWayAccess(const ITwoWayAccess& twoWayAccess) = default;
    ITwoWayAccess& operator=(const ITwoWayAccess& twoWayAccess) = default;
    ITwoWayAccess(ITwoWayAccess&& twoWayAccess) = default;
    ITwoWayAccess& operator=(ITwoWayAccess&& twoWayAccess) = default;
    virtual ~ITwoWayAccess() = default;

    virtual T& Front() = 0;
    virtual const T& Front() const = 0;

    virtual T& Back() = 0;
    virtual const T& Back() const = 0;
};
