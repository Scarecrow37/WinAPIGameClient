#pragma once
#include "../Component.h"
#include "../../../Interfaces/ITransform.h"

class ShapeComponent : public Component, public ITransform
{
public:
    ShapeComponent(Transform* worldTransform);
    ShapeComponent(Transform* worldTransform, const Transform& transform);

    Transform GetTransform() override;

protected:
    Transform _transform;
};
