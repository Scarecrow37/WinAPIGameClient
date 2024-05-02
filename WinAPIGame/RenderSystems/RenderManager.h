#pragma once
#include "IRenderSystem.h"

class RenderManager final : public IRenderSystem
{
public:
    RenderManager();

    void Finalize() override;
    void Initialize() override;
    void SetRenderer(IRenderer* renderer) override;
    IRenderer* GetRenderer() const override;

    void DrawLine(int x1, int y1, int x2, int y2, unsigned long color) override;
    void DrawRectangle(int x, int y, int width, int height, unsigned long color) override;
    void DrawCircle(int x, int y, int radius, unsigned long color) override;
    void DrawPolygon(tagPoint* points, int count, unsigned long color) override;
    void DrawString(int x, int y, const char* text, unsigned long color) override;
    void DrawFont(int x, int y, const char* text, unsigned long color, int fontSize, const wchar_t* fontName,
                  int fontStyle) override;
    void DrawImage(int x, int y, int width, int height, const wchar_t* filePath) const override;
    void DrawImage(int x, int y, int width, int height, const wchar_t* filePath, int sourceX, int sourceY,
                   int sourceWidth, int sourceHeight, unsigned long excludeColor) override;

private:
    int ReverseVertical(int y) const;
    void OriginToCenter(int& x, int& y) const;
    void OriginToCenter(long& x, long& y) const;

private:
    IRenderer* _renderer;
};
