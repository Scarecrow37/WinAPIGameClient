#include "HardBody.h"

#include "../../../Game/Objects/Floor.h"
#include "../../../Math/Math.h"
#include "../../../Models/Transform/Transform.h"

HardBody::HardBody(Transform* worldTransform, ICollision* instance, const Rectangle& collisionRectangle,
                   bool movable): Collider(
                                      worldTransform, instance, collisionRectangle), _movable(movable)
{
}

void HardBody::FixedUpdate()
{
    // // Floor 임시로
    // if (_movable && _current && dynamic_cast<Floor*>(_other))
    // {
    //     auto [oMin, oMax] = _other->GetCollider()->GetBounds();
    //     auto [min, max] = _instance->GetCollider()->GetBounds();
    //     // _worldTransform->location.x = Math::Clamp(_worldTransform->location.x, min.x, max.x);
    //     if (min.y < oMax.y) _worldTransform->location.y = oMax.y + (_worldTransform->location.y - min.y);
    //     //_worldTransform->location.y = Math::Clamp(_worldTransform->location.y, min.y, max.y);
    // }
    Collider::FixedUpdate();
}
