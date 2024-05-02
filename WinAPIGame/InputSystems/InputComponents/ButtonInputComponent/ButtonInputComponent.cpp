#include "ButtonInputComponent.h"

ButtonInputComponent::ButtonInputComponent(): _previous(false), _current(false), _on(false), _started(false),
                                              _ended(false)
{
}

bool ButtonInputComponent::IsOn() const
{
    return _on;
}

bool ButtonInputComponent::IsStarted() const
{
    return _started;
}


bool ButtonInputComponent::IsEnded() const
{
    return _ended;
}

void ButtonInputComponent::Initialize()
{
    _on = false;
    _started = false;
    _ended = false;
    _previous = false;
    _current = false;
}

void ButtonInputComponent::Start()
{
    _on = true;
    _started = true;
}

void ButtonInputComponent::SetValue(const bool value)
{
    _current = value;
    if (!_previous && _current)
    {
        Start();
    }
    else if (_previous && !_current)
    {
        End();
    }
    _previous = _current;
}

void ButtonInputComponent::End()
{
    _on = false;
    _ended = true;
}

void ButtonInputComponent::Reset()
{
    _started = false;
    _ended = false;
}

float ButtonInputComponent::GetInputValue() const
{
    return _on ? 1.f : 0.f;
}
