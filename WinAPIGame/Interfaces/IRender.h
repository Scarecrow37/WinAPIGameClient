#pragma once

class IDraw;

class IRender
{
public:
    IRender() = default;
    IRender(const IRender& other) = default;
    IRender(IRender&& other) noexcept = default;
    IRender& operator=(const IRender& other) = default;
    IRender& operator=(IRender&& other) noexcept = default;
    virtual ~IRender() = default;

    virtual void Render(IDraw* renderSystem) = 0;
};

