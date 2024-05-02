#pragma once

class IGetButtonState
{
public:
    IGetButtonState() = default;
    IGetButtonState(const IGetButtonState& other) = default;
    IGetButtonState(IGetButtonState&& other) noexcept = default;
    IGetButtonState& operator=(const IGetButtonState& other) = default;
    IGetButtonState& operator=(IGetButtonState&& other) noexcept = default;
    virtual ~IGetButtonState() = default;

    virtual bool IsOn() const = 0;
    virtual bool IsStarted() const = 0;
    virtual bool IsEnded() const = 0;
};
