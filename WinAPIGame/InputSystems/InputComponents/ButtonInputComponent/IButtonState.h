#pragma once
#include "IGetButtonState.h"

class IButtonState : public IGetButtonState
{
public:
    virtual void Start() = 0;
    virtual void End() = 0;
    virtual void SetValue(bool value) = 0;
};
