// MMP2 Project made by: Nicolas van Renen, Andrè Linder
#include "stdafx.h"

#include "PlayerHealthComponent.hpp"
#include "HealthPowerUpComponent.hpp"
#include "MainState.hpp"
#include "GameStateManager.hpp"
#include "PlayerHealthComponent.hpp"


void mmt_gd::HealthPowerUpComponent::applyPowerUp(GameObject& player)
{
    //check if the player has a health component
    auto healthComponent = player.getComponent<HealthComponent>();
    if (healthComponent)
    {
        // dereference the pointer and add the health increment
        healthComponent->addHealth(m_healthIncrement);
    }
    else
    {
        std::cerr << "HealthComponent not found for player" << std::endl;
    }
}


void mmt_gd::HealthPowerUpComponent::removePowerUp(GameObject& player)
{
}

bool mmt_gd::HealthPowerUpComponent::init()
{
    return true;
}

void mmt_gd::HealthPowerUpComponent::update(float deltaTime)
{
}
