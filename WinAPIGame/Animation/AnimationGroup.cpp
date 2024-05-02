#include "AnimationGroup.h"

#include "../StateMachine/State.h"
#include "../StateMachine/StateMachine.h"

AnimationGroup::AnimationGroup(StateMachine* stateMachine): _increaseId(0), _stateMachine(stateMachine)
{
}

void AnimationGroup::AddAnimation(State* state, Animation* animation)
{
    state->SetId(_increaseId++);
    _animations.PushBack(animation);
}

Animation* AnimationGroup::GetAnimation()
{
    return _animations[_stateMachine->GetCurrentState()->GetId()];
}

void AnimationGroup::Update()
{
    _stateMachine->Update();
}
