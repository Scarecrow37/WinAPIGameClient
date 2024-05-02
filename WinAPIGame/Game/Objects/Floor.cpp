#include "Floor.h"
#include "../../Engine/Components/ShapeComponent/RectangleComponent/RectangleShape.h"
#include "../../Engine/Components/PhysicsComponent/HardBody.h"

Floor::Floor()
{
    _transform.location.y = -256;
    _rectangleComponent = new RectangleShape(&_transform, {512, 48, 512, 48}, 0x000000);
    AddComponent(_rectangleComponent);
    _collider = new HardBody(&_transform, this, {512, 48, 512, 48}, false);
    AddComponent(_collider);
}

Floor::~Floor()
{
    delete _rectangleComponent;
    delete _collider;
}

Collider* Floor::GetCollider()
{
    return _collider;
}

void Floor::OnCollision(ICollision* other)
{
}

void Floor::OnCollisionStart(ICollision* other)
{
}

void Floor::OnCollisionEnd(ICollision* other)
{
}
