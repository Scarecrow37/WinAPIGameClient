#include "SimpleClock.h"

SimpleClock::SimpleClock(): _previousClock(0), _currentClock(0), _deltaClock(0)
{
}

float SimpleClock::GetDeltaTime()
{
    return static_cast<float>(_deltaClock) / CLOCKS_PER_SEC;
    
}

int SimpleClock::GetDeltaTimeMillisecond()
{
    return static_cast<int>(_deltaClock);
}

void SimpleClock::Initialize()
{
    _previousClock = _currentClock = clock();
}

void SimpleClock::Update()
{
    _currentClock = clock();
    _deltaClock = _currentClock - _previousClock;
    _previousClock = _currentClock;
}
