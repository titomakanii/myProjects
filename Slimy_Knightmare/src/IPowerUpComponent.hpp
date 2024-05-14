#pragma once

#include "IComponent.hpp"
//class GameObject;
namespace mmt_gd
{
class IPowerUpComponent : public IComponent
{

public:
    IPowerUpComponent(GameObject& gameObject) : IComponent(gameObject)
    {
    }

    virtual void applyPowerUp(GameObject& player)  = 0;
    virtual void removePowerUp(GameObject& player) = 0;


private:
};
} // namespace mmt_gd