#pragma once

namespace Math
{
    template <typename T>
    static T Clamp(T value, T min, T max)
    {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }

    template <typename T>
    static T Absolute(T value)
    {
        if (value < 0) return -value;
        return value;
    }
}
