#pragma once

class ISlideState
{
public:
    virtual void SetValue(long value) = 0;
    virtual void SetSensitivity(long sensitivity) = 0;
    virtual void SetDeadZone(float deadZone) = 0;
};
