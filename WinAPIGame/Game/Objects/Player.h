#pragma once
#include "../../Engine/Object/Object.h"
#include "../../InputSystems/EnhancedInputSystem/IEnhancedInputObject.h"
#include "../../Interfaces/ICollision.h"
#include "../../Models/ActionValue/ActionValue.h"

class HardBody;
class GravityComponent;
class AnimationSprite;
class InputAction;

class Player final : public Object, public IEnhancedInputObject, public ICollision
{
    // enum State : unsigned char
    // {
    //     Idle,
    //     Walk
    // };

public:
    Player(const wchar_t* name);
    ~Player() override;

    void SetMovementAction(InputAction* movementAction);
    void SetJumpAction(InputAction* jumpAction);

    void OnCollision(ICollision* other) override;
    Collider* GetCollider() override;
    void OnCollisionStart(ICollision* other) override;
    void OnCollisionEnd(ICollision* other) override;
    void SetPosition(const Vector& vector);

    void Update(float deltaTime) override;
    void FixedUpdate() override;

private:
    void OnMoveAction(const ActionValue& value);
    void Jump(const ActionValue& value);
    bool IsMove() const;
    bool IsRun() const;
    bool IsJump() const;

    InputAction* _movementAction;
    InputAction* _jumpAction;

    AnimationSprite* _animationComponent;
    GravityComponent* _gravityComponent;
    HardBody* _collider;

    wchar_t* _idleFile;
    wchar_t* _walkFile;
    wchar_t* _runFile;
    wchar_t* _jumpFile;

    float _speed;
    float _jumpScale;
    Vector _velocity;
    Vector _yVelocity;
    bool _isJumping;

    Vector _virtualVelocity;
};
