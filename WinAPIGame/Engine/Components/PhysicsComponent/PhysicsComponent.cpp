#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(Transform* worldTransform, Vector* velocity): Component(worldTransform)
    , _velocity(velocity)
{
}
