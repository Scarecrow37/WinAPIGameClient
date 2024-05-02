#pragma once

class Collider;

class ICollision
{
public:
    ICollision() = default;
    ICollision(const ICollision& other) = default;
    ICollision(ICollision&& other) noexcept = default;
    ICollision& operator=(const ICollision& other) = default;
    ICollision& operator=(ICollision&& other) noexcept = default;
    virtual ~ICollision() = default;

    virtual void OnCollisionStart(ICollision* other) = 0;
    virtual void OnCollisionEnd(ICollision* other) = 0;
    virtual void OnCollision(ICollision* other) = 0;
    virtual Collider* GetCollider() = 0;
};
