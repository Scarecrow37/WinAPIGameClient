#pragma once
#include "../ITimeSystem.h"
#include <Windows.h>

class QueryClock final : public ITimeSystem
{
public:
    QueryClock();

    float GetDeltaTime() override;
    int GetDeltaTimeMillisecond() override;
    void Initialize() override;
    void Update() override;

private:
    LARGE_INTEGER _frequency;
    LARGE_INTEGER _previousTick;
    LARGE_INTEGER _currentTick;
    LARGE_INTEGER _deltaTick;
};
