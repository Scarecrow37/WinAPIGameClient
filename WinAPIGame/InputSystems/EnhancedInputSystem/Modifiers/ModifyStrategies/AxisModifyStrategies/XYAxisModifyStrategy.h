#pragma once
#include "IAxisModifyStrategy.h"

class Modifier;

class XYAxisModifyStrategy final : public IAxisModifyStrategy
{
public:
    void Modify(ActionValue& value) const override;

private:
    XYAxisModifyStrategy() = default;
    friend Modifier;
};
