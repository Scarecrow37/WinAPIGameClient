#include "InvokerSet.h"

#include "../Invokers/IInvoker.h"

void InvokerSet::AddInvoker(IInvoker* invoker)
{
    _invokers.PushBack(invoker);
}

ActionValue InvokerSet::GetActionValue() const
{
    ActionValue value{};
    for (const auto& invoker : _invokers)
    {
        value += invoker->GetActionValue();
    }
    return value;
}

InvokerSet::~InvokerSet()
{
    for (const IInvoker* invoker : _invokers)
    {
        delete invoker;
    }
}
