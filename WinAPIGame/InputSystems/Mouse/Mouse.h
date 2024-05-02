#pragma once
#include "../IInputSystem.h"
#include "../InputComponents/ButtonInputComponent/ButtonInputComponent.h"
#include "../InputComponents/SlideInputComponent/SlideInputComponent.h"

class Mouse final : public IInputSystem
{
public:
    enum class Component : unsigned char
    {
        X,
        Y,
        Wheel,
        LeftButton,
        RightButton,
        MiddleButton
    };

    void Initialize() override;
    void Update() override;
    void Reset() override;
    const IInputValue* GetInputValueGetter(unsigned char componentCode) const override;
    const IInputValue* GetInputValueGetter(Component mouseComponent) const;

private:
    SlideInputComponent _x;
    SlideInputComponent _y;
    SlideInputComponent _wheel;
    ButtonInputComponent _left;
    ButtonInputComponent _right;
    ButtonInputComponent _middle;
};
