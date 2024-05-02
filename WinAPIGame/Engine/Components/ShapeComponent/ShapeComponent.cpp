#include "ShapeComponent.h"

ShapeComponent::ShapeComponent(Transform* worldTransform) : Component(worldTransform), _transform({})
{
}

ShapeComponent::ShapeComponent(Transform* worldTransform, const Transform& transform) : Component(worldTransform),
    _transform(transform)
{
}

Transform ShapeComponent::GetTransform()
{
    return _transform;
}
