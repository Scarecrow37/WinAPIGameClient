#include "ActionValue.h"

ActionValue::operator bool() const
{
    return on || scalar != 0.f || vector.x != 0.f || vector.y != 0.f;
}

ActionValue& ActionValue::operator+=(const ActionValue& rhs)
{
    vector.x += rhs.vector.x;
    vector.y += rhs.vector.y;
    return *this;
}
