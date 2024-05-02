#pragma once

class IReset
{
public:
    IReset() = default;
    IReset(const IReset& other) = default;
    IReset(IReset&& other) noexcept = default;
    IReset& operator=(const IReset& other) = default;
    IReset& operator=(IReset&& other) noexcept = default;
    virtual ~IReset() = default;

    virtual void Reset() = 0;
};
