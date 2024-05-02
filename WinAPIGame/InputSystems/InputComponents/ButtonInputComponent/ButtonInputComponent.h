#pragma once
#include "IButtonState.h"
#include "../IInputValue.h"
#include "../../IReset.h"
#include "../../../Interfaces/IInitialize.h"

class ButtonInputComponent final : public IInitialize, public IInputValue, public IButtonState, public IReset
{
public:
    ButtonInputComponent();
    
    bool IsOn() const override;
    bool IsStarted() const override;
    bool IsEnded() const override;
    
    void Initialize() override;
    void Start() override;
    void SetValue(bool value) override;
    void End() override;
    void Reset() override;
    
    float GetInputValue() const override;

private:
    bool _previous;
    bool _current;
    
    bool _on;
    bool _started;
    bool _ended;
};
