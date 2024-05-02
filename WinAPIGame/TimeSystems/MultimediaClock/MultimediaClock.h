#pragma once
#include "../ITimeSystem.h"
#include <Windows.h>

class MultimediaClock final : public ITimeSystem
{
public:
    MultimediaClock();
    
    float GetDeltaTime() override;
    int GetDeltaTimeMillisecond() override;
    void Initialize() override;
    void Update() override;

private:
    DWORD _previousTime;
    DWORD _currentTime;
    DWORD _deltaTime;
};
