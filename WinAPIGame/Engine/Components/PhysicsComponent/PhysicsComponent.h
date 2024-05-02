#pragma once
#include "../Component.h"
#include "../../../Models/Vector/Vector.h"

class PhysicsComponent : public Component
{
public:
    PhysicsComponent(Transform* worldTransform, Vector* velocity);
    

protected:
    Vector* _velocity;
};
