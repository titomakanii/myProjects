#pragma once

#include "GameObject.hpp"
#include "IPowerUpComponent.hpp"


namespace mmt_gd
{
class SpeedPowerUpComponent : public IPowerUpComponent
{
public:
    SpeedPowerUpComponent(GameObject& gameObject) : IPowerUpComponent(gameObject)
    {
    }

    void applyPowerUp(GameObject& player) override;
    void removePowerUp(GameObject& player) override;

    bool init() override;
    void update(float deltaTime) override;

private:
};
} // namespace mmt_gd