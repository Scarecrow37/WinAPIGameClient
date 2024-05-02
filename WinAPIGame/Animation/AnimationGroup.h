#pragma once
#include "../Containers/Vector.h"
#include "../Interfaces/IUpdate.h"

class State;
class StateMachine;
class Animation;

class AnimationGroup : public IUpdate
{
public:
    AnimationGroup(StateMachine* stateMachine);
    void AddAnimation(State* state, Animation* animation);
    Animation* GetAnimation();
    void Update() override;

private:
    int _increaseId;
    StateMachine* _stateMachine;
    Dosuha::Vector<Animation*> _animations;
};
