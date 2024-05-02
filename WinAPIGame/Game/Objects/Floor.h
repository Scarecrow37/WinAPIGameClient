#pragma once
#include "../../Engine/Object/Object.h"
#include "../../Interfaces/ICollision.h"

class HardBody;class Collider;
class RectangleShape;

class Floor final : public Object, public ICollision
{
public:
    Floor();
    ~Floor();

    Collider* GetCollider() override;
    void OnCollision(ICollision* other) override;
    void OnCollisionStart(ICollision* other) override;
    void OnCollisionEnd(ICollision* other) override;

private:
    RectangleShape* _rectangleComponent;
    HardBody* _collider;
};
