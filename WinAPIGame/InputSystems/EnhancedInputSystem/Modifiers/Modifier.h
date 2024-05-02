#pragma once
#include "IModifier.h"

class InverseDirectionModifyStrategy;
class ForwardDirectionModifyStrategy;
class YXAxisModifyStrategy;
class XYAxisModifyStrategy;

class Modifier final : public IModifier
{
public:
    static const XYAxisModifyStrategy XYStrategy;
    static const YXAxisModifyStrategy YXStrategy;
    static const ForwardDirectionModifyStrategy ForwardStrategy;
    static const InverseDirectionModifyStrategy InverseStrategy;

    Modifier();

    void Modify(ActionValue& value) const override;
    void SetStrategy(const IAxisModifyStrategy& strategy) override;
    void SetStrategy(const IDirectionModifyStrategy& strategy) override;

private:
    const IAxisModifyStrategy* _axisStrategy;
    const IDirectionModifyStrategy* _directionStrategy;
};
