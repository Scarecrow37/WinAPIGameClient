#include "YXAxisModifyStrategy.h"
#include "../../../../../Models/ActionValue/ActionValue.h"

void YXAxisModifyStrategy::Modify(ActionValue& value) const
{
    ActionValue result;
    result.vector.x = value.vector.y;
    result.vector.y = value.vector.x;
    value = result;
}
