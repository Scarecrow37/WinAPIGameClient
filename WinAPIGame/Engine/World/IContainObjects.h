#pragma once
#include "../../Containers/Vector.h"

class ICollision;
class Object;

class IContainObjects
{
public:
    IContainObjects() = default;
    IContainObjects(const IContainObjects& other) = default;
    IContainObjects(IContainObjects&& other) noexcept = default;
    IContainObjects& operator=(const IContainObjects& other) = default;
    IContainObjects& operator=(IContainObjects&& other) noexcept = default;
    virtual ~IContainObjects() = default;

    virtual const Dosuha::Vector<ICollision*>& GetCollisions() const = 0;
    virtual void AddObject(Object* object) = 0;
};
