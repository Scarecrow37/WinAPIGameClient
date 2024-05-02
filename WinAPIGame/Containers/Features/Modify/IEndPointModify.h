#pragma once

template <typename T>
class IEndPointModify
{
public:
    IEndPointModify() = default;
    IEndPointModify(const IEndPointModify& endPointModifier) = default;
    IEndPointModify& operator=(const IEndPointModify& endPointModifier) = default;
    IEndPointModify(IEndPointModify&& endPointModifier) = default;
    IEndPointModify& operator=(IEndPointModify&& endPointModifier) = default;
    virtual ~IEndPointModify() = default;

    virtual void Push(const T& value) = 0;
    virtual void Pop() = 0;
};
