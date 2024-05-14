#pragma once

#include "IComponent.hpp"
#include "RigidBodyComponent.hpp"

namespace mmt_gd
{

class PlayerMoveComponent : public IComponent
{
public:
    using ptr = std::shared_ptr<PlayerMoveComponent>;

    PlayerMoveComponent(GameObject& gameObject, RigidBodyComponent& rigidBody, int playerIndex);

    bool init() override;
    void update(float deltaTime) override;
    sf::Vector2f getCurrentPosition() const;
    float getDashCooldown() const;
    float getCooldownTimer() const;
    bool getIsDashOnCooldown() const;

private:
    int m_playerIndex;

    float m_dashCooldown;
    bool  m_isDashOnCooldown;
    float m_dashTimer;
    float m_dashDuration;
    bool  m_isDashActive;
    float m_cooldownTimer;



 

    RigidBodyComponent& m_rigidBody;
};
} // namespace mmt_gd
