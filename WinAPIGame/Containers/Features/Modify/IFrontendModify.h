#pragma once

template <typename T>
class IFrontendModify
{
public:
    IFrontendModify() = default;
    IFrontendModify(const IFrontendModify& backendModifier) = default;
    IFrontendModify& operator=(const IFrontendModify& backendModifier) = default;
    IFrontendModify(IFrontendModify&& backendModifier) = default;
    IFrontendModify& operator=(IFrontendModify&& backendModifier) = default;
    virtual ~IFrontendModify() = default;

    virtual void PushFront(const T& value) = 0;
    virtual void PopFront() = 0;
};
