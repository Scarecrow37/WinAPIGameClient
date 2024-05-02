#pragma once
#include "Collider.h"

class HardBody : public Collider
{
public:
    HardBody(Transform* worldTransform, ICollision* instance, const Rectangle& collisionRectangle, bool movable);
    void FixedUpdate() override;

private:
    bool _movable;
};
