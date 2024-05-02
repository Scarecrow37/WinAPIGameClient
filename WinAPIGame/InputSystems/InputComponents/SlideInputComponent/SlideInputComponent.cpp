#include "SlideInputComponent.h"

#include "../../../Math/Math.h"

SlideInputComponent::SlideInputComponent(): _previousValue(0), _value(0), _sensitivity(100), _deadZone(0)
{
}

void SlideInputComponent::SetValue(const long value)
{
    _previousValue = _value;
    _value = value;
}

float SlideInputComponent::GetInputValue() const
{
    const long offset = _value - _previousValue;
    const float ratio = static_cast<float>(offset) / static_cast<float>(_sensitivity);
    if (Math::Absolute(ratio) < _deadZone) return 0.f;
    return ratio;
}

void SlideInputComponent::Reset()
{
    _previousValue = 0;
    _value = 0;
}

void SlideInputComponent::Initialize()
{
    _previousValue = 0;
    _value = 0;
}

void SlideInputComponent::SetSensitivity(const long sensitivity)
{
    _sensitivity = sensitivity;
}

void SlideInputComponent::SetDeadZone(const float deadZone)
{
    _deadZone = Math::Clamp(deadZone, 0.f, 1.f);
}
