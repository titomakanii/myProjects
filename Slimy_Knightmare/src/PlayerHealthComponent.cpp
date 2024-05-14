// MMP2 Project made by: Nicolas van Renen, Andrè Linder
// Music is copyrightfree and no author is required
#include "stdafx.h"

#include "PlayerMoveComponent.hpp"

#include "GameObject.hpp"
#include "InputManager.hpp"
#include "PlayerHealthComponent.hpp"

namespace mmt_gd
{
HealthComponent::HealthComponent(GameObject& gameObject, int initialHealth) :
IComponent(gameObject),
m_health(initialHealth),
m_damaged(false)
{
}
bool HealthComponent::init()
{
    return true;
}

void HealthComponent::update(float deltaTime)
{

}

int HealthComponent::getHealth() const
{
    return m_health;
}

void HealthComponent::addHealth(int amount)
{
    if (m_health + amount <= 200)
    {
        m_health += amount;
    }
    else
    {
        // max HP is 200
        m_health = 200;
    }
    if (!m_sound.openFromFile("../assets/Musik/Pickup.ogg"))
    {
        //std::cerr << "Failed to load music file" << std::endl;
    }
    else
    {
        m_sound.play();
    }
}

void HealthComponent::reduceHealth(int amount)
{
    m_health -= amount;

    if (m_health <= 0)
    {
        m_gameObject.setActive(false);
    }
    if (!m_sound.openFromFile("../assets/Musik/Hit.wav"))
    {
        //std::cerr << "Failed to load music file" << std::endl;
    }
    else
    {
        m_sound.play();
    }
    m_damaged = true;
}
} // namespace mmt_gd