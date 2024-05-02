#pragma once
#include "../IActionValue.h"

class IInvoker;

class IInvokerSet : public IActionValue
{
public:
    virtual void AddInvoker(IInvoker* invoker) = 0;
};
