#pragma once
#include "../ITimeSystem.h"
#include <ctime>

class SimpleClock final : public ITimeSystem
{
public:
    SimpleClock();

    float GetDeltaTime() override;
    int GetDeltaTimeMillisecond() override;
    void Initialize() override;
    void Update() override;

private:
    clock_t _previousClock;
    clock_t _currentClock;
    clock_t _deltaClock;
};
