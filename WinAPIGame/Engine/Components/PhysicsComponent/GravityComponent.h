#pragma once
#include "PhysicsComponent.h"
#include "../Component.h"
#include "../../../Models/Vector/Vector.h"

class GravityComponent final : public PhysicsComponent
{
public:
    explicit GravityComponent(Transform* worldTransform, Vector* velocity);
    void SetGravityScale(float scale);
    void Update(float deltaTime) override;
    void FixedUpdate() override;
    void Render(IDraw* renderSystem) override;
    void Start();
    void Stop();

private:
    float _gravityScale;
    bool _onAir;
    Vector _gravityVelocity;
};
