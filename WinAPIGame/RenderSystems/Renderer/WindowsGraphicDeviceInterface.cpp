#include "WindowsGraphicDeviceInterface.h"

#include "../../WindowsApplication.h"
#include "../../Math/Math.h"

#pragma comment(lib, "msimg32.lib")

WindowsGraphicDeviceInterface::WindowsGraphicDeviceInterface(): _window(nullptr),
                                                                _frontDeviceContext(nullptr),
                                                                _backDeviceContext(nullptr),
                                                                _backBitmap(nullptr)
{
}

void WindowsGraphicDeviceInterface::Initialize()
{
    _window = WindowsApplication::GetWindowHandle();
    _frontDeviceContext = GetDC(_window);
    _backDeviceContext = CreateCompatibleDC(_frontDeviceContext);
    _backBitmap = CreateCompatibleBitmap(_frontDeviceContext, WindowsApplication::GetScreenWidth(),
                                         WindowsApplication::GetScreenHeight());
}

void WindowsGraphicDeviceInterface::BeginDraw()
{
    CleanScreen();
    SelectObject(_backDeviceContext, _backBitmap);
}

void WindowsGraphicDeviceInterface::EndDraw()
{
    BitBlt(_frontDeviceContext, 0, 0, WindowsApplication::GetScreenWidth(), WindowsApplication::GetScreenHeight(),
           _backDeviceContext, 0, 0, SRCCOPY);
}

void WindowsGraphicDeviceInterface::Finalize()
{
    DeleteObject(_backBitmap);
    DeleteDC(_backDeviceContext);
    ReleaseDC(_window, _frontDeviceContext);
}

void WindowsGraphicDeviceInterface::DrawLine(const int x1, const int y1, const int x2, const int y2,
                                             const unsigned long color)
{
    const HPEN pen = CreatePen(PS_SOLID, 5, color);
    const HPEN oldPen = static_cast<HPEN>(SelectObject(_backDeviceContext, pen));
    MoveToEx(_backDeviceContext, x1, y1, nullptr);
    LineTo(_backDeviceContext, x2, y2);
    SelectObject(_backDeviceContext, oldPen);
    DeleteObject(pen);
}

void WindowsGraphicDeviceInterface::DrawRectangle(const int x, const int y, const int width, const int height,
                                                  const unsigned long color)
{
    const HPEN pen = CreatePen(PS_SOLID, 1, color);
    const HPEN oldPen = static_cast<HPEN>(SelectObject(_backDeviceContext, pen));
    const HBRUSH brush = CreateSolidBrush(color);
    const HBRUSH oldBrush = static_cast<HBRUSH>(SelectObject(_backDeviceContext, brush));
    Rectangle(_backDeviceContext, x, y, x + width, y + height);
    SelectObject(_backDeviceContext, oldPen);
    SelectObject(_backDeviceContext, oldBrush);
    DeleteObject(pen);
    DeleteObject(brush);
}

void WindowsGraphicDeviceInterface::DrawCircle(const int x, const int y, const int radius, const unsigned long color)
{
    const HPEN pen = CreatePen(PS_SOLID, 1, color);
    const HPEN oldPen = static_cast<HPEN>(SelectObject(_backDeviceContext, pen));
    const HBRUSH brush = CreateSolidBrush(color);
    const HBRUSH oldBrush = static_cast<HBRUSH>(SelectObject(_backDeviceContext, brush));
    Ellipse(_backDeviceContext, x - radius, y - radius, x + radius, y + radius);
    SelectObject(_backDeviceContext, oldPen);
    SelectObject(_backDeviceContext, oldBrush);
    DeleteObject(pen);
    DeleteObject(brush);
}

void WindowsGraphicDeviceInterface::DrawPolygon(tagPoint* points, const int count, const unsigned long color)
{
    const HPEN pen = CreatePen(PS_SOLID, 1, color);
    const HPEN oldPen = static_cast<HPEN>(SelectObject(_backDeviceContext, pen));
    const HBRUSH brush = CreateSolidBrush(color);
    const HBRUSH oldBrush = static_cast<HBRUSH>(SelectObject(_backDeviceContext, brush));
    Polygon(_backDeviceContext, reinterpret_cast<POINT*>(points), count);
    SelectObject(_backDeviceContext, oldPen);
    SelectObject(_backDeviceContext, oldBrush);
    DeleteObject(pen);
    DeleteObject(brush);
}

void WindowsGraphicDeviceInterface::DrawString(const int x, const int y, const char* text, const unsigned long color)
{
    const COLORREF oldColor = SetTextColor(_backDeviceContext, color);
    TextOutA(_backDeviceContext, x, y, text, static_cast<int>(strlen(text)));
    SetTextColor(_backDeviceContext, oldColor);
}

void WindowsGraphicDeviceInterface::DrawFont(const int x, const int y, const char* text, const unsigned long color,
                                             const int fontSize, const wchar_t* fontName, const int fontStyle)
{
    const HFONT font = CreateFont(fontSize, 0, 0, 0, fontStyle, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                                  OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
                                  fontName);
    const HFONT oldFont = static_cast<HFONT>(SelectObject(_backDeviceContext, font));
    DrawString(x, y, text, color);
    SelectObject(_backDeviceContext, oldFont);
    DeleteObject(font);
}

void WindowsGraphicDeviceInterface::DrawImage(const int x, const int y, const int width, const int height,
                                              const wchar_t* filePath) const
{
    const HDC dc = CreateCompatibleDC(_frontDeviceContext);
    const HBITMAP bitmapHandle = static_cast<HBITMAP>(LoadImage(nullptr, filePath, IMAGE_BITMAP, NULL, NULL,
                                                                LR_LOADFROMFILE));
    const HBITMAP oldBitmap = static_cast<HBITMAP>(SelectObject(dc, bitmapHandle));
    BitBlt(_backDeviceContext, x, y, width, height, dc, 0, 0, SRCCOPY);
    SelectObject(dc, oldBitmap);
    DeleteObject(bitmapHandle);
    DeleteDC(dc);
}

void WindowsGraphicDeviceInterface::DrawImage(int x, int y, int width, int height, const wchar_t* filePath, int sourceX,
                                              int sourceY, int sourceWidth, int sourceHeight,
                                              unsigned long excludeColor)
{
    const HDC bitmapDC = CreateCompatibleDC(_frontDeviceContext);
    const HBITMAP bitmapHandle = static_cast<HBITMAP>(LoadImage(nullptr, filePath, IMAGE_BITMAP, NULL, NULL,
                                                                LR_LOADFROMFILE));
    const HBITMAP oldBitmap = static_cast<HBITMAP>(SelectObject(bitmapDC, bitmapHandle));

    HDC flipDC = CreateCompatibleDC(_frontDeviceContext);
    HBITMAP flipBitmapHandle = CreateCompatibleBitmap(_frontDeviceContext, sourceWidth, sourceHeight);
    SelectObject(flipDC, flipBitmapHandle);
    StretchBlt(flipDC, width < 0 ? sourceWidth - 1 : 0, height < 0 ? sourceHeight - 1 : 0,
               width < 0 ? -sourceWidth - 1 : sourceWidth, height < 0 ? -sourceHeight - 1 : sourceHeight,
               bitmapDC, sourceX, sourceY, sourceWidth, sourceHeight, SRCCOPY);
    width = Math::Absolute(width);
    height = Math::Absolute(height);
    BITMAP bitmap;
    GetObject(bitmapHandle, sizeof(BITMAP), &bitmap);
    TransparentBlt(_backDeviceContext, x, y, width, height, flipDC, 0, 0,
                   sourceWidth, sourceHeight, excludeColor);
    DeleteObject(flipBitmapHandle);
    SelectObject(bitmapDC, oldBitmap);
    DeleteObject(bitmapHandle);
    DeleteDC(flipDC);
    DeleteDC(bitmapDC);
}

int WindowsGraphicDeviceInterface::GetWidth() const
{
    return WindowsApplication::GetClientWidth();
}

int WindowsGraphicDeviceInterface::GetHeight() const
{
    return WindowsApplication::GetClientHeight();
}

void WindowsGraphicDeviceInterface::CleanScreen() const
{
    PatBlt(_backDeviceContext, 0, 0, WindowsApplication::GetScreenWidth(), WindowsApplication::GetScreenHeight(),
           WHITENESS);
}
