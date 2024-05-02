#pragma once
#include "../../Interfaces/IDeltaUpdate.h"
#include "../../Interfaces/IFixedUpdate.h"
#include "../../Interfaces/IRender.h"

struct Transform;

class Component : public IDeltaUpdate, public IFixedUpdate, public IRender
{
public:
    Component(Transform* worldTransform);
protected:
    Transform* _worldTransform;
};
