#pragma once
#include "ModifyStrategies/AxisModifyStrategies/IAxisModifyStrategy.h"

class IDirectionModifyStrategy;
class IAxisModifyStrategy;

class IModifier : public IModifyStrategy
{
public:
    virtual void SetStrategy(const IAxisModifyStrategy& strategy) = 0;
    virtual void SetStrategy(const IDirectionModifyStrategy& strategy) = 0;
};
