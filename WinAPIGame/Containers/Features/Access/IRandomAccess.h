#pragma once

template <typename T>
class IRandomAccess
{
public:
    IRandomAccess() = default;
    IRandomAccess(const IRandomAccess& randomAccess) = default;
    IRandomAccess& operator=(const IRandomAccess& randomAccess) = default;
    IRandomAccess(IRandomAccess&& randomAccess) = default;
    IRandomAccess& operator=(IRandomAccess&& randomAccess) = default;
    virtual ~IRandomAccess() = default;

    virtual T& At(size_t position) = 0;
    virtual const T& At(size_t position) const = 0;

    virtual T& operator[](size_t position) = 0;
    virtual const T& operator[](size_t position) const = 0;

    virtual T* Data() = 0;
    virtual const T* Data() const = 0;
};
