#pragma once
#include "../IInputSystem.h"
#include "../InputComponents/ButtonInputComponent/ButtonInputComponent.h"

class Keyboard final : public IInputSystem
{
    static constexpr unsigned char NumberOfKeys = 0xFF;

public:
    void Initialize() override;
    void Update() override;
    void Reset() override;
    const IInputValue* GetInputValueGetter(unsigned char keyCode) const override;

private:
    ButtonInputComponent _keys[NumberOfKeys];
};
