#pragma once

class Component;

class IContainComponents
{
public:
    IContainComponents() = default;
    IContainComponents(const IContainComponents& other) = default;
    IContainComponents(IContainComponents&& other) noexcept = default;
    IContainComponents& operator=(const IContainComponents& other) = default;
    IContainComponents& operator=(IContainComponents&& other) noexcept = default;
    virtual ~IContainComponents() = default;

    virtual void AddComponent(Component* component) = 0;
};
