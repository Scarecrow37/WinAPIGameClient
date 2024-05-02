#include "RenderManager.h"
#include "Renderer/IRenderer.h"
#include <Windows.h>

#include "../GameManager.h"

RenderManager::RenderManager() : _renderer(nullptr)
{
}

void RenderManager::Finalize()
{
    _renderer->Finalize();
}

void RenderManager::Initialize()
{
    _renderer->Initialize();
}

void RenderManager::SetRenderer(IRenderer* renderer)
{
    _renderer = renderer;
}

IRenderer* RenderManager::GetRenderer() const
{
    return _renderer;
}

void RenderManager::DrawLine(int x1, int y1, int x2, int y2, unsigned long color)
{
    OriginToCenter(x1, y1);
    OriginToCenter(x2, y2);
    _renderer->DrawLine(x1, ReverseVertical(y1), x2, ReverseVertical(y2), color);
}

void RenderManager::DrawRectangle(int x, int y, int width, int height, unsigned long color)
{
    OriginToCenter(x, y);
    _renderer->DrawRectangle(x, ReverseVertical(y), width, height, color);
}

void RenderManager::DrawCircle(int x, int y, int radius, unsigned long color)
{
    OriginToCenter(x, y);
    _renderer->DrawCircle(x, ReverseVertical(y), radius, color);
}

void RenderManager::DrawPolygon(tagPoint* points, int count, unsigned long color)
{
    POINT* rePoints = reinterpret_cast<POINT*>(points);
    for (int i = 0; i < count; ++i)
    {
        OriginToCenter(rePoints[i].x, rePoints[i].y);
        rePoints[i].y = ReverseVertical(rePoints[i].y);
    }
    _renderer->DrawPolygon(points, count, color);
}

void RenderManager::DrawString(int x, int y, const char* text, unsigned long color)
{
    OriginToCenter(x, y);
    _renderer->DrawString(x, ReverseVertical(y), text, color);
}

void RenderManager::DrawFont(int x, int y, const char* text, unsigned long color, int fontSize, const wchar_t* fontName,
                             int fontStyle)
{
    OriginToCenter(x, y);
    _renderer->DrawFont(x, ReverseVertical(y), text, color, fontSize, fontName, fontStyle);
}

void RenderManager::DrawImage(int x, int y, int width, int height, const wchar_t* filePath) const
{
    OriginToCenter(x, y);
    _renderer->DrawImage(x, ReverseVertical(y), width, height, filePath);
}

void RenderManager::DrawImage(int x, int y, int width, int height, const wchar_t* filePath, int sourceX, int sourceY,
                              int sourceWidth, int sourceHeight, unsigned long excludeColor)
{
    OriginToCenter(x, y);
    _renderer->DrawImage(x, ReverseVertical(y), width, height, filePath, sourceX, sourceY, sourceWidth, sourceHeight, excludeColor);
}

int RenderManager::ReverseVertical(int y) const
{
    return _renderer->GetHeight() - y;
}

void RenderManager::OriginToCenter(int& x, int& y) const
{
    x += _renderer->GetWidth() / 2;
    y += _renderer->GetHeight() / 2;
}

void RenderManager::OriginToCenter(long& x, long& y) const
{
    x += _renderer->GetWidth() / 2;
    y += _renderer->GetHeight() / 2;
}
