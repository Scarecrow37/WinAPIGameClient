#include "GravityComponent.h"

GravityComponent::GravityComponent(Transform* worldTransform, Vector* velocity):
    PhysicsComponent(worldTransform, velocity), _gravityScale(2.f),
    _onAir(true), _gravityVelocity(Vector::Zero)
{
}

void GravityComponent::SetGravityScale(const float scale)
{
    _gravityScale = scale;
}

void GravityComponent::Update(const float deltaTime)
{
    if (!_onAir) return;
    *_velocity += Vector::Down * _gravityScale;
}

void GravityComponent::FixedUpdate()
{
}

void GravityComponent::Render(IDraw* renderSystem)
{
}

void GravityComponent::Start()
{
    _onAir = true;
}

void GravityComponent::Stop()
{
    _onAir = false;
    _gravityVelocity = Vector::Zero;
}
