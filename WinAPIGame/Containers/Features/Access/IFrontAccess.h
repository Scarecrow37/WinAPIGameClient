#pragma once

template <typename T>
class IFrontAccess
{
public:
    IFrontAccess() = default;
    IFrontAccess(const IFrontAccess& oneWayAccess) = default;
    IFrontAccess& operator=(const IFrontAccess& oneWayAccess) = default;
    IFrontAccess(IFrontAccess&& oneWayAccess) = default;
    IFrontAccess& operator=(IFrontAccess&& oneWayAccess) = default;
    virtual ~IFrontAccess() = default;

    virtual T& Front() = 0;
    virtual const T& Front() const = 0;
};
