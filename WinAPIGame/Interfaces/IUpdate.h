#pragma once

class IUpdate
{
public:
    IUpdate() = default;
    IUpdate(const IUpdate& other) = default;
    IUpdate(IUpdate&& other) noexcept = default;
    IUpdate& operator=(const IUpdate& other) = default;
    IUpdate& operator=(IUpdate&& other) noexcept = default;
    virtual ~IUpdate() = default;
    
    virtual void Update() = 0;
};
