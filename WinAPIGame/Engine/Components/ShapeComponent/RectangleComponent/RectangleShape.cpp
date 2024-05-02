#include "RectangleShape.h"

#include "../../../../RenderSystems/IDraw.h"

RectangleShape::RectangleShape(Transform* worldTransform, const Rectangle rectangle, const unsigned long color) :
    ShapeComponent(worldTransform), _rectangle(rectangle),
    _color(color)
{
}

RectangleShape::RectangleShape(Transform* worldTransform, const Transform& transform, const Rectangle rectangle,
                               const unsigned long color) : ShapeComponent(worldTransform, transform),
                                                            _rectangle(rectangle),
                                                            _color(color)
{
}

void RectangleShape::Update(float deltaTime)
{
}

void RectangleShape::FixedUpdate()
{
}

void RectangleShape::Render(IDraw* renderSystem)
{
    const Vector location = _transform.location + _worldTransform->location;
    renderSystem->DrawRectangle(static_cast<int>(location.x - _rectangle.left),
                                static_cast<int>(location.y + _rectangle.top),
                                static_cast<int>(_rectangle.left + _rectangle.right),
                                static_cast<int>(_rectangle.top + _rectangle.bottom), _color);
}

Transform RectangleShape::GetTransform()
{
    return _transform;
}
