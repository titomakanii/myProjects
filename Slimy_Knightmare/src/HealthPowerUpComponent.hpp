#pragma once

#include "GameObject.hpp"
#include "IPowerUpComponent.hpp"
#include "MainState.hpp"


namespace mmt_gd
{

class HealthPowerUpComponent : public IPowerUpComponent
{
public:
    HealthPowerUpComponent(GameObject& gameObject) : IPowerUpComponent(gameObject)
    {
    }

    void applyPowerUp(GameObject& player) override;
    void removePowerUp(GameObject& player) override;

    bool init() override;
    void update(float deltaTime) override;

private:
    int m_healthIncrement = 10;
};
} // namespace mmt_gd