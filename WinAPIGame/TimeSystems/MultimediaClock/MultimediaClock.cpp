#include "MultimediaClock.h"

#pragma comment (lib, "winmm.lib")

MultimediaClock::MultimediaClock(): _previousTime(0), _currentTime(0), _deltaTime(0)
{
}

float MultimediaClock::GetDeltaTime()
{
    return static_cast<float>(_deltaTime) / 1000.f;
}

int MultimediaClock::GetDeltaTimeMillisecond()
{
    return static_cast<int>(_deltaTime);
}

void MultimediaClock::Initialize()
{
    _previousTime = _currentTime = timeGetTime();
}

void MultimediaClock::Update()
{
    _currentTime = timeGetTime();
    _deltaTime = _currentTime - _previousTime;
    _previousTime = _currentTime;
}
