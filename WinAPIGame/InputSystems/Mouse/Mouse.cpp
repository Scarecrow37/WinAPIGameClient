#include "Mouse.h"
#include <Windows.h>

#include "../../WindowsApplication.h"


void Mouse::Initialize()
{
    _x.Initialize();
    _y.Initialize();
    _wheel.Initialize();
    _left.Initialize();
    _right.Initialize();
    _middle.Initialize();
}

void Mouse::Update()
{
    /*POINT mousePosition;
    GetCursorPos(&mousePosition);
    ScreenToClient(WindowsApplication::GetWindowHandle(), &mousePosition);

    _x.SetValue(mousePosition.x);
    _y.SetValue(mousePosition.y);

    // TODO Refactor this
    MSG message;
    if (PeekMessage(&message, WindowsApplication::GetWindowHandle(), NULL, NULL, PM_NOREMOVE)
        && message.message == WM_MOUSEWHEEL)
        _wheel.SetValue(GET_WHEEL_DELTA_WPARAM(message.wParam));

    _left.SetValue(GetKeyState(VK_LBUTTON) & 0x8000);
    _right.SetValue(GetKeyState(VK_RBUTTON) & 0x8000);
    _middle.SetValue(GetKeyState(VK_LBUTTON) & 0x8000);*/
}

void Mouse::Reset()
{
    _x.Reset();
    _y.Reset();
    _wheel.Reset();
    _left.Reset();
    _right.Reset();
    _middle.Reset();
}

const IInputValue* Mouse::GetInputValueGetter(unsigned char componentCode) const
{
    return GetInputValueGetter(static_cast<Component>(componentCode));
}

const IInputValue* Mouse::GetInputValueGetter(const Component mouseComponent) const
{
    switch (mouseComponent)
    {
    case Component::X:
        return &_x;
    case Component::Y:
        return &_y;
    case Component::Wheel:
        return &_wheel;
    case Component::LeftButton:
        return &_left;
    case Component::RightButton:
        return &_right;
    case Component::MiddleButton:
        return &_middle;
    }
    return nullptr;
}
