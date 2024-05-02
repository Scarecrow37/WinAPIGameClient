#pragma once
#include "../Component.h"
#include "../../../Interfaces/ICollision.h"
#include "../../../Models/Bounds/Bounds.h"
#include "../../../Models/Rectangle/Rectangle.h"

class ICollision;

class Collider : public Component
{
public:
    Collider(Transform* worldTransform, ICollision* instance, Rectangle collisionRectangle);
    Collider(const Collider& other) = default;
    Collider(Collider&& other) noexcept = default;
    Collider& operator=(const Collider& other) = default;
    Collider& operator=(Collider&& other) noexcept = default;

    ~Collider() override = default;

    virtual void Collide(ICollision* other);
    Bounds GetBounds() const;

    void Update(float deltaTime) override;
    void FixedUpdate() override;
    void Render(IDraw* renderSystem) override;

protected:
    ICollision* _instance;
    Rectangle _collisionRectangle;
    ICollision* _other;
    bool _previous;
    bool _current;
};
