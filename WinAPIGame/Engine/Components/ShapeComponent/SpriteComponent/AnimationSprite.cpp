#include "AnimationSprite.h"
#include "../../../../Animation/Animation.h"
#include "../../../../Animation/AnimationGroup.h"
#include "../../../../RenderSystems/IDraw.h"
#include "../../../../StateMachine/State.h"

AnimationSprite::AnimationSprite(Transform* worldTransform, const Rectangle spriteRectangle, AnimationGroup* animation):
    ShapeComponent(worldTransform), _spriteRectangle(spriteRectangle), _animationGroup(animation), _pivot(0),
    _flipX(false),
    _flipY(false)
{
}

void AnimationSprite::Update(float deltaTime)
{
    static float elapsedTime;
    _animationGroup->Update();
    elapsedTime += deltaTime;
    Animation* animation = _animationGroup->GetAnimation();
    while (elapsedTime > animation->GetFrame(_pivot).interval)
    {
        if (animation->GetFrame(_pivot).onEnd) animation->GetFrame(_pivot).onEnd();
        elapsedTime -= animation->GetFrame(_pivot).interval;
        _pivot = ++_pivot % animation->GetFrameCount();
        if (animation->GetFrame(_pivot).onStart) animation->GetFrame(_pivot).onStart();
    }
}

void AnimationSprite::FixedUpdate()
{
}

void AnimationSprite::Render(IDraw* renderSystem)
{
    auto [interval, filePath, region, excludeColor, onStart, onEnd] = _animationGroup->GetAnimation()->
        GetFrame(_pivot);
    int x = static_cast<int>(_worldTransform->location.x + _transform.location.x);
    x -= static_cast<int>(_flipX ? _spriteRectangle.right: _spriteRectangle.left);
    int y = static_cast<int>(_worldTransform->location.y + _transform.location.y);
    y += static_cast<int>(_flipY ? _spriteRectangle.bottom : _spriteRectangle.top);
    int width = static_cast<int>(_spriteRectangle.GetWidth() * (_flipX ? -1.f: 1.f));
    int height = static_cast<int>(_spriteRectangle.GetHeight() * (_flipY ? -1.f : 1.f));
    renderSystem->DrawImage(x, y, width, height, filePath, region.x,
                            region.y, region.width, region.height, excludeColor);
}

void AnimationSprite::ResetToFirstFrame()
{
    _pivot = 0;
}

void AnimationSprite::Flip(const bool flipX, const bool flipY)
{
    _flipX = flipX;
    _flipY = flipY;
}
