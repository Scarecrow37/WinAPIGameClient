#pragma once
#include <Windows.h>
#include <Xinput.h>
#include "../IInputSystem.h"
#include "../InputComponents/ButtonInputComponent/ButtonInputComponent.h"
#include "../InputComponents/SlideInputComponent/SlideInputComponent.h"

class Controller final : public IInputSystem
{
    static constexpr DWORD Disconnection = -1;
    static constexpr long ThumbStickSensitive = 32767;
    static constexpr float ThumbDefaultDeadZone = 0.1f;
    static constexpr long TriggerSensitive = 255;

public:
    enum Component : unsigned char
    {
        DpadUp,
        DpadDown,
        DpadLeft,
        DpadRight,
        Start,
        Back,
        LeftThumb,
        RightThumb,
        LeftShoulder,
        RightShoulder,
        A,
        B,
        X,
        Y,
        LeftTrigger,
        RightTrigger,
        LeftThumbX,
        LeftThumbY,
        RightThumbX,
        RightThumbY
    };

    Controller();
    void Initialize() override;
    void Update() override;
    void Reset() override;
    const IInputValue* GetInputValueGetter(unsigned char componentCode) const override;
    const IInputValue* GetInputValueGetter(const Component& component) const;

private:
    static unsigned short GetFlag(const Component& component);

    bool CheckConnection();

    DWORD _controllerIndex;

    ButtonInputComponent _dpadUp;
    ButtonInputComponent _dpadDown;
    ButtonInputComponent _dpadLeft;
    ButtonInputComponent _dpadRight;
    ButtonInputComponent _start;
    ButtonInputComponent _back;
    ButtonInputComponent _leftThumb;
    ButtonInputComponent _rightThumb;
    ButtonInputComponent _leftShoulder;
    ButtonInputComponent _rightShoulder;
    ButtonInputComponent _a;
    ButtonInputComponent _b;
    ButtonInputComponent _x;
    ButtonInputComponent _y;
    SlideInputComponent _leftTrigger;
    SlideInputComponent _rightTrigger;
    SlideInputComponent _leftThumbX;
    SlideInputComponent _leftThumbY;
    SlideInputComponent _rightThumbX;
    SlideInputComponent _rightThumbY;
};
