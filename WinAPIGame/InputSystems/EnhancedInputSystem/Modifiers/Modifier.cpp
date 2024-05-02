#include "Modifier.h"
#include "ModifyStrategies/AxisModifyStrategies/XYAxisModifyStrategy.h"
#include "ModifyStrategies/AxisModifyStrategies/YXAxisModifyStrategy.h"
#include "ModifyStrategies/DirectionModifyStrategies/ForwardDirectionModifyStrategy.h"
#include "ModifyStrategies/DirectionModifyStrategies/InverseDirectionModifyStrategy.h"

const XYAxisModifyStrategy Modifier::XYStrategy;
const YXAxisModifyStrategy Modifier::YXStrategy;
const ForwardDirectionModifyStrategy Modifier::ForwardStrategy;
const InverseDirectionModifyStrategy Modifier::InverseStrategy;

Modifier::Modifier(): _axisStrategy(&XYStrategy), _directionStrategy(&ForwardStrategy)
{
}


void Modifier::Modify(ActionValue& value) const
{
    _axisStrategy->Modify(value);
    _directionStrategy->Modify(value);
}

void Modifier::SetStrategy(const IAxisModifyStrategy& strategy)
{
    _axisStrategy = &strategy;
}

void Modifier::SetStrategy(const IDirectionModifyStrategy& strategy)
{
    _directionStrategy = &strategy;
}
