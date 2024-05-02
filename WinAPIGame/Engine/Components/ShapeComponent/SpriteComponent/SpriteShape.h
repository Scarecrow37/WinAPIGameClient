#pragma once
#include "../ShapeComponent.h"
#include "../../../../Models/Rectangle/Rectangle.h"
#include "../../../../Models/Region/Region.h"

class SpriteShape final : public ShapeComponent
{
public:
    SpriteShape(Transform* worldTransform, Rectangle spriteRectangle, const wchar_t* filePath, Region imageRegion,
                    unsigned long excludeColor);
    void Update(float deltaTime) override;
    void FixedUpdate() override;
    void Render(IDraw* renderSystem) override;

private:
    Rectangle _spriteRectangle;
    const wchar_t* _file;
    Region _imageRegion;
    unsigned long _excludeColor;
};
