#include "Player.h"

#include <iostream>

#include "Floor.h"
#include "../../GameManager.h"
#include "../../Animation/Animation.h"
#include "../../Animation/AnimationGroup.h"
#include "../../InputSystems/EnhancedInputSystem/InputAction/InputAction.h"
#include "../../Models/ActionValue/ActionValue.h"
#include "../../Engine/Components/ShapeComponent/SpriteComponent/AnimationSprite.h"
#include "../../Engine/Components/PhysicsComponent/GravityComponent.h"
#include "../../Engine/Components/PhysicsComponent/HardBody.h"
#include "../../Engine/Components/ShapeComponent/RectangleComponent/RectangleShape.h"
#include "../../Math/Math.h"
#include "../../StateMachine/State.h"
#include "../../StateMachine/StateMachine.h"
#include "../../TimeSystems/IDeltaTime.h"

void CopyAndAppend(wchar_t*& buffer, const wchar_t* name, const wchar_t* tail)
{
    const size_t idleLength = wcslen(name) + wcslen(tail) + 1;
    buffer = new wchar_t[idleLength];
    wcscpy_s(buffer, idleLength, name);
    wcscat_s(buffer, idleLength, tail);
}


Player::Player(const wchar_t* name) : _speed(300.0f), _jumpScale(400.f), _velocity(Vector::Zero),
                                      _yVelocity(Vector::Zero),
                                      _isJumping(false), _virtualVelocity(Vector::Zero)
{
    CopyAndAppend(_idleFile, name, L"_idle.bmp");
    CopyAndAppend(_walkFile, name, L"_walk.bmp");
    CopyAndAppend(_runFile, name, L"_run.bmp");
    CopyAndAppend(_jumpFile, name, L"_jump.bmp");

    State* idle = new State;
    State* run = new State;
    State* walk = new State;
    State* jump = new State;
    idle->AddArrow({[this] { return IsJump(); }, jump});
    idle->AddArrow({[this] { return IsRun(); }, run});
    idle->AddArrow({[this] { return IsMove(); }, walk});

    run->AddArrow({[this] { return IsJump(); }, jump});
    run->AddArrow({[this] { return IsMove() && !IsRun(); }, walk});
    run->AddArrow({[this] { return !IsMove(); }, idle});

    walk->AddArrow({[this] { return IsJump(); }, jump});
    walk->AddArrow({[this] { return IsRun(); }, run});
    walk->AddArrow({[this] { return !IsMove(); }, idle});

    jump->AddArrow({[this] { return !IsJump() && IsRun(); }, run});
    jump->AddArrow({[this] { return !IsJump() && IsMove(); }, walk});
    jump->AddArrow({[this] { return !IsJump(); }, idle});

    StateMachine* stateMachine = new StateMachine(idle);

    AnimationGroup* animationGroup = new AnimationGroup(stateMachine);
    animationGroup->AddAnimation(idle, Animation::Builder::GetInstance().Initialize().AddFrame({
                                     0.2f, _idleFile, {0, 0, 48, 48}, 0xFF00FF, nullptr, nullptr
                                 }).AddFrame().AddFrame().AddFrame().Build());
    animationGroup->AddAnimation(walk, Animation::Builder::GetInstance().Initialize().AddFrame({
                                     0.2f, _walkFile, {0, 0, 48, 48}, 0xFF00FF, nullptr, nullptr
                                 }).AddFrame().AddFrame().AddFrame().AddFrame().AddFrame().Build());
    animationGroup->AddAnimation(run, Animation::Builder::GetInstance().Initialize().AddFrame({
                                     0.15f, _runFile, {0, 0, 48, 48}, 0xFF00FF, nullptr, nullptr
                                 }).AddFrame().AddFrame().AddFrame().AddFrame().AddFrame().Build());
    animationGroup->AddAnimation(jump, Animation::Builder::GetInstance().Initialize().AddFrame({
                                     0.15f, _jumpFile, {0, 0, 48, 48}, 0xFF00FF, nullptr, nullptr
                                 }).AddFrame().AddFrame().AddFrame().AddFrame().AddFrame().NotLoop().Build());


    _animationComponent = new AnimationSprite(&_transform, {32, 48, 64, 48}, animationGroup);
    stateMachine->BindOnStateChanged([this] { _animationComponent->ResetToFirstFrame(); });
    AddComponent(_animationComponent);
    _gravityComponent = new GravityComponent(&_transform, &_yVelocity);
    AddComponent(_gravityComponent);
    _collider = new HardBody(&_transform, this, {48, 48, 48, 48}, true);
    AddComponent(_collider);
}

Player::~Player()
{
    delete _animationComponent;
    delete _gravityComponent;
    delete[] _idleFile;
    delete[] _walkFile;
    delete[] _jumpFile;
    delete[] _runFile;
}

void Player::SetMovementAction(InputAction* movementAction)
{
    _movementAction = movementAction;
    _movementAction->BindEffect(InputAction::TriggerType::Triggered, this, &Player::OnMoveAction);
}

void Player::SetJumpAction(InputAction* jumpAction)
{
    _jumpAction = jumpAction;
    jumpAction->BindEffect(InputAction::TriggerType::Started, this, &Player::Jump);
}

void Player::OnMoveAction(const ActionValue& value)
{
    _velocity = value.vector * _speed;
}

void Player::Jump(const ActionValue& value)
{
    if (_isJumping) return;
    _yVelocity += Vector::Up * _jumpScale;
    _isJumping = true;
}

void Player::OnCollision(ICollision* other)
{
    if (!dynamic_cast<Floor*>(other)) return;
    Bounds otherBounds = other->GetCollider()->GetBounds();
    Bounds bounds = GetCollider()->GetBounds();
    if (bounds.min.y < otherBounds.max.y) _transform.location.y = otherBounds.max.y + (_transform.location.y - bounds.
        min.y);
}

Collider* Player::GetCollider()
{
    return _collider;
}

void Player::OnCollisionStart(ICollision* other)
{
    if (dynamic_cast<Floor*>(other))
    {
        _gravityComponent->Stop();
        _isJumping = false;
        _yVelocity = Vector::Zero;
    }
}

void Player::OnCollisionEnd(ICollision* other)
{
    if (dynamic_cast<Floor*>(other)) _gravityComponent->Start();
}

void Player::SetPosition(const Vector& vector)
{
    _virtualVelocity += ((vector - _transform.location) / GameManager::GetTime()->GetDeltaTime());
    if (!_isJumping && _virtualVelocity.y > 0) _isJumping = true;
    _transform.location = vector;
}

void Player::Update(float deltaTime)
{
    Object::Update(deltaTime);
    if (_velocity.x < 0 || _virtualVelocity.x < 0) _animationComponent->Flip(true, false);
    else if (_velocity.x > 0 || _virtualVelocity.x > 0) _animationComponent->Flip(false, false);
    _transform.location += (_velocity + _yVelocity) * deltaTime;
    _velocity = Vector::Zero;
}

void Player::FixedUpdate()
{
    Object::FixedUpdate();
    _virtualVelocity = Vector::Zero;
}

bool Player::IsMove() const
{
    return Math::Absolute(_velocity.x) > 0 || Math::Absolute(_virtualVelocity.x) > 0;
}

bool Player::IsRun() const
{
    return Math::Absolute(_velocity.x) > _speed * 0.5f || Math::Absolute(_virtualVelocity.x) > _speed * 0.5f;
}

bool Player::IsJump() const
{
    return _isJumping;
}
