#pragma once
#include "IInvokerSet.h"
#include "../../../Containers/Vector.h"

class InvokerSet final : public IInvokerSet
{
public:
    InvokerSet() = default;
    InvokerSet(const InvokerSet& other) = default;
    InvokerSet(InvokerSet&& other) noexcept = default;
    InvokerSet& operator=(const InvokerSet& other) = default;
    InvokerSet& operator=(InvokerSet&& other) noexcept = default;
    ~InvokerSet() override;

    void AddInvoker(IInvoker* invoker) override;
    ActionValue GetActionValue() const override;

private:
    Dosuha::Vector<IInvoker*> _invokers;
};
