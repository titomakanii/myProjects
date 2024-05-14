// HealthComponent.hpp

#pragma once

#include "IComponent.hpp"

namespace mmt_gd
{
class HealthComponent : public IComponent
{
public:
    HealthComponent(GameObject& gameObject, int initialHealth);

    int  getHealth() const;
    void reduceHealth(int amount);
    void addHealth(int amount);

    bool init() override;
    void update(float deltaTime) override;

    bool isDamaged() const
    {
        return m_damaged;
    } // Function to check if health decreased in the current frame

private:
    int m_health;
    sf::Music m_sound;
    bool      m_damaged;
};
} // namespace mmt_gd