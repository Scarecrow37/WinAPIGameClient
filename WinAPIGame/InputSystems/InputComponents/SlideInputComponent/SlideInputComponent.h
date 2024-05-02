#pragma once
#include "ISlideState.h"
#include "../IInputValue.h"
#include "../../IReset.h"
#include "../../../Interfaces/IInitialize.h"

class SlideInputComponent final : public IInitialize, public IInputValue, public ISlideState, public IReset
{
public:
    SlideInputComponent();
    void SetValue(long value) override;
    float GetInputValue() const override;
    void Reset() override;
    void Initialize() override;
    void SetSensitivity(long sensitivity) override;
    void SetDeadZone(float deadZone) override;

private:
    long _previousValue;
    long _value;
    long _sensitivity;
    float _deadZone;
};
