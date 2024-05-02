#include "QueryClock.h"

QueryClock::QueryClock(): _frequency({}), _previousTick({}), _currentTick({}), _deltaTick({})
{
}


float QueryClock::GetDeltaTime()
{
    return static_cast<float>(_deltaTick.QuadPart) / static_cast<float>(_frequency.QuadPart);
}

int QueryClock::GetDeltaTimeMillisecond()
{
    return static_cast<int>(_deltaTick.QuadPart / _frequency.QuadPart) * 1000;
}

void QueryClock::Initialize()
{
    QueryPerformanceFrequency(&_frequency);
    QueryPerformanceCounter(&_previousTick);
}

void QueryClock::Update()
{
    QueryPerformanceCounter(&_currentTick);
    _deltaTick.QuadPart = _currentTick.QuadPart - _previousTick.QuadPart;
    _previousTick = _currentTick;
}
