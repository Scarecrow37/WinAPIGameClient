#pragma once
#include "IDirectionModifyStrategy.h"

class Modifier;

class ForwardDirectionModifyStrategy final : public IDirectionModifyStrategy
{
public:
    void Modify(ActionValue& value) const override;

private:
    ForwardDirectionModifyStrategy() = default;
    friend Modifier;
};
