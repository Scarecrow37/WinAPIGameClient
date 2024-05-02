#include "SpriteShape.h"

#include "../../../../RenderSystems/IDraw.h"

SpriteShape::SpriteShape(Transform* worldTransform, const Rectangle spriteRectangle, const wchar_t* filePath,
                                 Region imageRegion, const unsigned long excludeColor):
    ShapeComponent(worldTransform), _spriteRectangle(spriteRectangle), _file(filePath), _imageRegion(imageRegion),
    _excludeColor(excludeColor)
{
}

void SpriteShape::Update(float deltaTime)
{
}

void SpriteShape::FixedUpdate()
{
}

void SpriteShape::Render(IDraw* renderSystem)
{
    renderSystem->DrawImage(
        static_cast<int>(_worldTransform->location.x + _transform.location.x - _spriteRectangle.left),
        static_cast<int>(_worldTransform->location.y + _transform.location.y + _spriteRectangle.top),
        static_cast<int>(_spriteRectangle.GetWidth()), static_cast<int>(_spriteRectangle.GetHeight()), _file,
        _imageRegion.x, _imageRegion.y, _imageRegion.width, _imageRegion.height, _excludeColor);
}
