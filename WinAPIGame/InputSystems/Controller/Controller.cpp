#include "Controller.h"

#pragma comment(lib, "xinput.lib")

Controller::Controller(): _controllerIndex(Disconnection)
{
}

void Controller::Initialize()
{
    _dpadUp.Initialize();
    _dpadDown.Initialize();
    _dpadLeft.Initialize();
    _dpadRight.Initialize();
    _start.Initialize();
    _back.Initialize();
    _leftThumb.Initialize();
    _rightThumb.Initialize();
    _leftShoulder.Initialize();
    _rightShoulder.Initialize();
    _a.Initialize();
    _b.Initialize();
    _x.Initialize();
    _y.Initialize();
    _leftTrigger.Initialize();
    _leftTrigger.SetSensitivity(TriggerSensitive);
    _rightTrigger.Initialize();
    _rightTrigger.SetSensitivity(TriggerSensitive);
    _leftThumbX.Initialize();
    _leftThumbX.SetSensitivity(ThumbStickSensitive);
    _leftThumbX.SetDeadZone(ThumbDefaultDeadZone);
    _leftThumbY.Initialize();
    _leftThumbY.SetSensitivity(ThumbStickSensitive);
    _leftThumbY.SetDeadZone(ThumbDefaultDeadZone);
    _rightThumbX.Initialize();
    _rightThumbX.SetSensitivity(ThumbStickSensitive);
    _rightThumbX.SetDeadZone(ThumbDefaultDeadZone);
    _rightThumbY.Initialize();
    _rightThumbY.SetSensitivity(ThumbStickSensitive);
    _rightThumbY.SetDeadZone(ThumbDefaultDeadZone);
}

void Controller::Update()
{
    if (_controllerIndex == Disconnection && CheckConnection()) return;
    XINPUT_STATE state{};
    if (XInputGetState(_controllerIndex, &state) != ERROR_SUCCESS)
    {
        _controllerIndex = Disconnection;
        return;
    }
    _leftThumbX.SetValue(state.Gamepad.sThumbLX);
    _leftThumbY.SetValue(state.Gamepad.sThumbLY);
    _rightThumbX.SetValue(state.Gamepad.sThumbRX);
    _rightThumbX.SetValue(state.Gamepad.sThumbRY);
    _leftTrigger.SetValue(state.Gamepad.bLeftTrigger);
    _rightTrigger.SetValue(state.Gamepad.bRightTrigger);

    _dpadUp.SetValue(GetFlag(Component::DpadUp) & state.Gamepad.wButtons);
    _dpadDown.SetValue(GetFlag(Component::DpadDown) & state.Gamepad.wButtons);
    _dpadLeft.SetValue(GetFlag(Component::DpadLeft) & state.Gamepad.wButtons);
    _dpadRight.SetValue(GetFlag(Component::DpadRight) & state.Gamepad.wButtons);
    _start.SetValue(GetFlag(Component::Start) & state.Gamepad.wButtons);
    _back.SetValue(GetFlag(Component::Back) & state.Gamepad.wButtons);
    _leftThumb.SetValue(GetFlag(Component::LeftThumb) & state.Gamepad.wButtons);
    _rightThumb.SetValue(GetFlag(Component::RightThumb) & state.Gamepad.wButtons);
    _leftShoulder.SetValue(GetFlag(Component::LeftShoulder) & state.Gamepad.wButtons);
    _rightShoulder.SetValue(GetFlag(Component::RightShoulder) & state.Gamepad.wButtons);
    _a.SetValue(GetFlag(Component::A) & state.Gamepad.wButtons);
    _b.SetValue(GetFlag(Component::B) & state.Gamepad.wButtons);
    _x.SetValue(GetFlag(Component::X) & state.Gamepad.wButtons);
    _y.SetValue(GetFlag(Component::Y) & state.Gamepad.wButtons);
}

void Controller::Reset()
{
    _dpadUp.Reset();
    _dpadDown.Reset();
    _dpadLeft.Reset();
    _dpadRight.Reset();
    _start.Reset();
    _back.Reset();
    _leftThumb.Reset();
    _rightThumb.Reset();
    _leftShoulder.Reset();
    _rightShoulder.Reset();
    _a.Reset();
    _b.Reset();
    _x.Reset();
    _y.Reset();
    _leftTrigger.Reset();
    _rightTrigger.Reset();
    _leftThumbX.Reset();
    _leftThumbY.Reset();
    _rightThumbX.Reset();
    _rightThumbY.Reset();
}

const IInputValue* Controller::GetInputValueGetter(unsigned char componentCode) const
{
    return GetInputValueGetter(static_cast<Component>(componentCode));
}

const IInputValue* Controller::GetInputValueGetter(const Component& component) const
{
    switch (component)
    {
    case Component::DpadUp:
        return &_dpadUp;
    case Component::DpadDown:
        return &_dpadDown;
    case Component::DpadLeft:
        return &_dpadLeft;
    case Component::DpadRight:
        return &_dpadRight;
    case Component::Start:
        return &_start;
    case Component::Back:
        return &_back;
    case Component::LeftThumb:
        return &_leftThumb;
    case Component::RightThumb:
        return &_rightThumb;
    case Component::LeftShoulder:
        return &_leftShoulder;
    case Component::RightShoulder:
        return &_rightShoulder;
    case Component::A:
        return &_a;
    case Component::B:
        return &_b;
    case Component::X:
        return &_x;
    case Component::Y:
        return &_y;
    case Component::LeftTrigger:
        return &_leftTrigger;
    case Component::RightTrigger:
        return &_rightTrigger;
    case Component::LeftThumbX:
        return &_leftThumbX;
    case Component::LeftThumbY:
        return &_leftThumbY;
    case Component::RightThumbX:
        return &_rightThumbX;
    case Component::RightThumbY:
        return &_rightThumbY;
    }
    return nullptr;
}

unsigned short Controller::GetFlag(const Component& component)
{
    int flag = 1;
    for (int i = 0; i < static_cast<int>(component); ++i)
    {
        flag = flag << 1;
    }
    return static_cast<unsigned short>(flag);
}

bool Controller::CheckConnection()
{
    for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
    {
        XINPUT_STATE state{};
        auto result = XInputGetState(i, &state);
        if (result == ERROR_SUCCESS)
        {
            _controllerIndex = i;
            break;
        }
    }
    return _controllerIndex != Disconnection;
}
