#pragma once
#include "IDirectionModifyStrategy.h"

class Modifier;

class InverseDirectionModifyStrategy final : public IDirectionModifyStrategy
{
public:
    void Modify(ActionValue& value) const override;

private:
    InverseDirectionModifyStrategy() = default;
    friend Modifier;
};
