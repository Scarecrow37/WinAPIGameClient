#pragma once

template <typename T>
class IBackendModify
{
public:
    IBackendModify() = default;
    IBackendModify(const IBackendModify& backendModifier) = default;
    IBackendModify& operator=(const IBackendModify& backendModifier) = default;
    IBackendModify(IBackendModify&& backendModifier) = default;
    IBackendModify& operator=(IBackendModify&& backendModifier) = default;
    virtual ~IBackendModify() = default;

    virtual void PushBack(const T& value) = 0;
    virtual void PopBack() = 0;
};
