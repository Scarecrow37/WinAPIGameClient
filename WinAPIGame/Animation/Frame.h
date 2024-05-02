#pragma once
#include <functional>

#include "../Models/Region/Region.h"

struct Frame
{
    float interval;
    const wchar_t* filePath;
    Region region;
    unsigned long excludeColor;
    std::function<void()> onStart;
    std::function<void()> onEnd;
};
