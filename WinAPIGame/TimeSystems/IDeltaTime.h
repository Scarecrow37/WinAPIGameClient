#pragma once

class IDeltaTime
{
public:
    IDeltaTime() = default;
    IDeltaTime(const IDeltaTime& other) = default;
    IDeltaTime(IDeltaTime&& other) noexcept = default;
    IDeltaTime& operator=(const IDeltaTime& other) = default;
    IDeltaTime& operator=(IDeltaTime&& other) noexcept = default;
    virtual ~IDeltaTime() = default;

    virtual float GetDeltaTime() = 0;
    virtual int GetDeltaTimeMillisecond() = 0;
};
