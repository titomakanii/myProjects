#include "EnemyStateMachineComponent.hpp"
#include "stdafx.h"
#include "EnemyStateMachineComponent.hpp"
#include "GameObject.hpp"

namespace mmt_gd
{
EnemyStateMachineComponent::EnemyStateMachineComponent(GameObject* gameObject)
	: Component(gameObject)
{
}
void EnemyStateMachineComponent::update(float delta, State currentState)
{
    switch (currentState)
    {
        case STATE_PATROL:
            std::cout << "Performing patrol action" << std::endl;
            // do patrol action
            break;
        case STATE_ATTACK:
            std::cout << "Performing attack action" << std::endl;
            // do attack action
            break;
        case STATE_FLEE:
            std::cout << "Performing flee action" << std::endl;
            // do flee action
            break;
    }
}
bool EnemyStateMachineComponent::init()
{
    return false;
}
} // namespace mmt_gd