#pragma once
#include "IComponent.hpp"

namespace mmt_gd
{
enum State
{
    STATE_PATROL,
    STATE_ATTACK,
    STATE_FLEE
};

class EnemyStateMachineComponent : public IComponent
{
    public:
    void update(float delta, State currentState);
    bool init() override;
};
} // namespace mmt_gd