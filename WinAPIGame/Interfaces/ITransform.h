#pragma once
#include "../Models/Transform/Transform.h"


class ITransform
{
public:
    ITransform() = default;
    ITransform(const ITransform& other) = default;
    ITransform(ITransform&& other) noexcept = default;
    ITransform& operator=(const ITransform& other) = default;
    ITransform& operator=(ITransform&& other) noexcept = default;
    virtual ~ITransform() = default;

    virtual Transform GetTransform() = 0;
};
