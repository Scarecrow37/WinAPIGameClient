#pragma once
#include "../IActionValue.h"
#include "../IModifiable.h"
#include "../ITriggerable.h"

class IInvoker : public ITriggerable, public IModifiable, public IActionValue
{
};
