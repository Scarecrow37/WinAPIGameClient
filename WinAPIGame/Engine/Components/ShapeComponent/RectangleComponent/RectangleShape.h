#pragma once
#include "../ShapeComponent.h"
#include "../../../../Models/Rectangle/Rectangle.h"

class RectangleShape final : public ShapeComponent
{
public:
    RectangleShape(Transform* worldTransform, Rectangle rectangle, unsigned long color);
    RectangleShape(Transform* worldTransform, const Transform& transform, Rectangle rectangle, unsigned long color);

    void Update(float deltaTime) override;
    void FixedUpdate() override;
    void Render(IDraw* renderSystem) override;
    Transform GetTransform() override;

private:
    Rectangle _rectangle;
    unsigned long _color;
};
