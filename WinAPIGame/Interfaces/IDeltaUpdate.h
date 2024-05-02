#pragma once

class IDeltaUpdate
{
public:
    IDeltaUpdate() = default;
    IDeltaUpdate(const IDeltaUpdate& other) = default;
    IDeltaUpdate(IDeltaUpdate&& other) noexcept = default;
    IDeltaUpdate& operator=(const IDeltaUpdate& other) = default;
    IDeltaUpdate& operator=(IDeltaUpdate&& other) noexcept = default;
    virtual ~IDeltaUpdate() = default;

    virtual void Update(float deltaTime) = 0;
};
