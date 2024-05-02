#pragma once
#include "../ITimeSystem.h"
#include <Windows.h>

class TickClock final : public ITimeSystem
{
public:
    TickClock();

    float GetDeltaTime() override;
    int GetDeltaTimeMillisecond() override;
    void Initialize() override;
    void Update() override;

private:
    ULONGLONG _previousTime;
    ULONGLONG _currentTime;
    ULONGLONG _deltaTime;
};
