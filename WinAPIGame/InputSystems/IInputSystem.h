#pragma once
#include "IContainInputValues.h"
#include "IReset.h"
#include "../Interfaces/IInitialize.h"
#include "../Interfaces/IUpdate.h"

class IInputSystem : public IInitialize, public IUpdate, public IReset, public IContainInputValues
{
};
