#pragma once
#include "SpriteShape.h"

class AnimationGroup;
class Animation;

class AnimationSprite final : public ShapeComponent
{
public:
    AnimationSprite(Transform* worldTransform, Rectangle spriteRectangle, AnimationGroup* animation);
    void Update(float deltaTime) override;
    void FixedUpdate() override;
    void Render(IDraw* renderSystem) override;
    void ResetToFirstFrame();
    void Flip(bool flipX, bool flipY);
private:
    Rectangle _spriteRectangle;
    AnimationGroup* _animationGroup;
    size_t _pivot;
    bool _flipX;
    bool _flipY;
};
