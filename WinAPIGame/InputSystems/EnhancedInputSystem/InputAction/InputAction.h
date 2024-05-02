#pragma once
#include <functional>

#include "../IEnhancedInputObject.h"
#include "../../../Containers/Vector.h"
#include "../../../Interfaces/IUpdate.h"
#include "../Modifiers/ModifyStrategies/AxisModifyStrategies/IAxisModifyStrategy.h"
#include "../Modifiers/ModifyStrategies/DirectionModifyStrategies/IDirectionModifyStrategy.h"

class IEnhancedInputObject;
class IDirectionModifyStrategy;
class IAxisModifyStrategy;
class IInputValue;
class InvokerSet;
class IInvokerSet;
union ActionValue;

class InputAction final : public IUpdate
{
    using EffectFunction = std::function<void(const ActionValue&)>;

public :
    enum class TriggerType
    {
        Started,
        Triggered,
        Completed
    };

    InputAction(const InputAction& other) = delete;
    InputAction(InputAction&& other) noexcept = delete;
    InputAction& operator=(const InputAction& other) = delete;
    InputAction& operator=(InputAction&& other) noexcept = delete;
    ~InputAction() override;

    void Update() override;

    template <typename T>
    void BindEffect(const TriggerType type, T* instance,
                    void (T::*function)(const ActionValue&))
    {
        static_assert(std::is_base_of<IEnhancedInputObject, T>::value,
                      "Instance must be a subclass of IEnhancedInputObject.");
        auto effect = [instance, function](const ActionValue& value)-> void
        {
            (instance->*function)(value);
        };
        switch (type)
        {
        case TriggerType::Started:
            _startedEffects.PushBack(effect);
            break;
        case TriggerType::Triggered:
            _triggeredEffects.PushBack(effect);
            break;
        case TriggerType::Completed:
            _completedEffects.PushBack(effect);
            break;
        }
    }

private:
    InputAction();
    void AddInvokerSet(IInvokerSet* invokerSet);
    Dosuha::Vector<IInvokerSet*> _sets;
    Dosuha::Vector<EffectFunction> _startedEffects;
    Dosuha::Vector<EffectFunction> _triggeredEffects;
    Dosuha::Vector<EffectFunction> _completedEffects;
    bool _previousState;
    bool _currentState;

public:
    class Builder
    {
    public:
        static Builder& GetInstance();

        Builder& Initialize();
        Builder& OpenInvokerSet();
        Builder& AddInvoker(const IInputValue* trigger);
        Builder& AddInvoker(const IInputValue* trigger, const IAxisModifyStrategy& strategy);
        Builder& AddInvoker(const IInputValue* trigger, const IDirectionModifyStrategy& strategy);
        Builder& AddInvoker(const IInputValue* trigger, const IAxisModifyStrategy& axisStrategy,
                            const IDirectionModifyStrategy& directionStrategy);
        Builder& CloseInvokerSet();

        InputAction* Build();

    private:
        Builder();
        InputAction* _inputAction;
        InvokerSet* _invokerSet;
    };
};
