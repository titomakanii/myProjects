#pragma once

#include "IComponent.hpp"
#include "RigidBodyComponent.hpp"

namespace mmt_gd
{
    class AIMovementComponent : public IComponent
    {
    public:
        using ptr = std::shared_ptr<AIMovementComponent>;

        AIMovementComponent(GameObject& gameObject, RigidBodyComponent& rigidBody, int enemyIdx);

        bool init() override;
        void update(float deltaTime) override;

        // Set the target position for the enemy to move towards
        void setTargetPosition(const sf::Vector2f& targetPosition);

    private:
        int                 m_enemyIdx;
        RigidBodyComponent& m_rigidBody;
        sf::Vector2f        m_targetPosition; // New member variable to store the target position
        float               m_speed;           // New member variable to store the current speed
        float               m_timer;           // New member variable to track elapsed time

    };
} // namespace mmt_gd
