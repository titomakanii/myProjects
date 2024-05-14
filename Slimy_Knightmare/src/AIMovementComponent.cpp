// MMP2 Project made by: Nicolas van Renen, Andrè Linder
#include "stdafx.h"

#include "AIMovementComponent.hpp"
#include "GameObject.hpp"
#include "RigidBodyComponent.hpp"
#include "AnimatedSprite.hpp"

#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

namespace mmt_gd
{
AIMovementComponent::AIMovementComponent(GameObject&         gameObject,
                                         RigidBodyComponent& rigidBody,
                                         const int           enemyIdx) :
IComponent(gameObject),
m_enemyIdx(enemyIdx),
m_rigidBody(rigidBody),
m_targetPosition(1000.f, 1000.f), // Set the target position
m_speed(100.0F),                  // Initial speed in pixels/second
m_timer(0.0F)                     // Initialize the timer
{
}

bool AIMovementComponent::init()
{
    return true;
}

void AIMovementComponent::update(const float deltaTime)
{
    m_timer += deltaTime;

    if (m_timer >= 5.0F)
    {
        m_speed += 15.0F;
        m_timer = 0.0F;
    }

    // Calculate the direction vector from current position to the target position
    sf::Vector2f direction = m_targetPosition - m_rigidBody.getPosition();

    // Normalize the direction vector
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0.0f)
    {
        direction /= length;
    }

    // Move the enemy towards the target position with the updated speed
    sf::Vector2f velocity = direction * m_speed * deltaTime;
    m_rigidBody.setPosition(m_rigidBody.getPosition() + velocity);

    auto enemySprite = m_gameObject.getComponent<SpriteAnimationComponent>();

    // Check if the enemy is moving horizontally and change animation accordingly
    if (direction.x < 0.0f)
    {
        enemySprite->changeAnimation(0);
    }
    else if (direction.x > 0.0f)
    {
        enemySprite->changeAnimation(1);
    }
}

void AIMovementComponent::setTargetPosition(const sf::Vector2f& targetPosition)
{
    m_targetPosition = targetPosition;
}
} // namespace mmt_gd
