#include "InverseDirectionModifyStrategy.h"
#include "../../../../../Models/ActionValue/ActionValue.h"

void InverseDirectionModifyStrategy::Modify(ActionValue& value) const
{
    value.vector.x = -value.vector.x;
    value.vector.y = -value.vector.y;
}
