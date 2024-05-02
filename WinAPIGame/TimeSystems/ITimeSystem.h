#pragma once
#include "IDeltaTime.h"
#include "../Interfaces/IInitialize.h"
#include "../Interfaces/IUpdate.h"

class ITimeSystem : public IInitialize, public IUpdate, public IDeltaTime
{
};
