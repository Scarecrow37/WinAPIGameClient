#pragma once
#include "IAxisModifyStrategy.h"

class Modifier;

class YXAxisModifyStrategy final : public IAxisModifyStrategy
{
public:
    void Modify(ActionValue& value) const override;

private:
    YXAxisModifyStrategy() = default;
    friend Modifier;
};
