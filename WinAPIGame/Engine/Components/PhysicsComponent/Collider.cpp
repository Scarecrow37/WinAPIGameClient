#include "Collider.h"

#include "../../../Models/Transform/Transform.h"

Collider::Collider(Transform* worldTransform, ICollision* instance, Rectangle collisionRectangle):
    Component(worldTransform),
    _instance(instance),
    _collisionRectangle(collisionRectangle), _other(nullptr), _previous(false), _current(false)
{
}

void Collider::Collide(ICollision* other)
{
    _current = true;
    _other = other;
}

Bounds Collider::GetBounds() const
{
    return Bounds{
        {
            _worldTransform->location.x - _collisionRectangle.left,
            _worldTransform->location.y - _collisionRectangle.bottom
        },
        {
            _worldTransform->location.x + _collisionRectangle.right,
            _worldTransform->location.y + _collisionRectangle.top
        }
    };
}

void Collider::Update(float deltaTime)
{
}

void Collider::FixedUpdate()
{
    if (!_previous && _current) _instance->OnCollisionStart(_other);
    if (_current) _instance->OnCollision(_other);
    if (_previous && !_current) _instance->OnCollisionEnd(_other);
    _previous = _current;
    _current = false;
}

void Collider::Render(IDraw* renderSystem)
{
}
