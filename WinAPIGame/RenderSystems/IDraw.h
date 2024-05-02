#pragma once

struct tagPoint;

class IDraw
{
public:
    IDraw() = default;
    IDraw(const IDraw& other) = default;
    IDraw(IDraw&& other) noexcept = default;
    IDraw& operator=(const IDraw& other) = default;
    IDraw& operator=(IDraw&& other) noexcept = default;
    virtual ~IDraw() = default;

    virtual void DrawLine(int x1, int y1, int x2, int y2, unsigned long color) = 0;
    virtual void DrawRectangle(int x, int y, int width, int height, unsigned long color) = 0;
    virtual void DrawCircle(int x, int y, int radius, unsigned long color) = 0;
    virtual void DrawPolygon(tagPoint* points, int count, unsigned long color) = 0;
    virtual void DrawString(int x, int y, const char* text, unsigned long color) = 0;
    virtual void DrawFont(int x, int y, const char* text, unsigned long color,
                          int fontSize, const wchar_t* fontName, int fontStyle) = 0;
    virtual void DrawImage(int x, int y, int width, int height, const wchar_t* filePath) const = 0;
    virtual void DrawImage(int x, int y, int width, int height, const wchar_t* filePath, int sourceX, int sourceY,
                           int sourceWidth, int sourceHeight, unsigned long excludeColor) = 0;
};
