// MMP2 Project made by: Nicolas van Renen, Andrè Linder
#include "stdafx.h"

#include "PlayerMoveComponent.hpp"

#include "GameObject.hpp"
#include "InputManager.hpp"
#include "RigidBodyComponent.hpp"
#include "AnimatedSprite.hpp"

namespace mmt_gd
{
PlayerMoveComponent::PlayerMoveComponent(GameObject& gameObject, RigidBodyComponent& rigidBody, const int playerIndex) :
IComponent(gameObject),
m_playerIndex(playerIndex),
m_rigidBody(rigidBody),
m_dashCooldown(2.0f),        // Set the cooldown time in seconds
m_dashDuration(0.2f),        // Set the dash duration in seconds
m_isDashActive(false),
m_isDashOnCooldown(false)
{
}

bool PlayerMoveComponent::init()
{
    return true;
}

sf::Vector2f PlayerMoveComponent::getCurrentPosition() const
{
    // Return the current position of the player
    return m_gameObject.getPosition();
}

float PlayerMoveComponent::getDashCooldown() const
{
    // Return the dash cooldown time
	return m_dashCooldown;
}

float PlayerMoveComponent::getCooldownTimer() const
{
    // Return the current cooldown timer
	return m_cooldownTimer;
}

bool PlayerMoveComponent::getIsDashOnCooldown() const
{
	// Return the current cooldown state
	return m_isDashOnCooldown;
}

void PlayerMoveComponent::update(const float deltaTime)
{
    const auto   speed     = 25000.0F; // pixels/second
    const auto   dashSpeed = 250'000.0F;
    sf::Vector2f translation{};
    auto         playerAni = m_gameObject.getComponent<SpriteAnimationComponent>();

 // Calculate normalized input vector
    sf::Vector2f inputDirection{};
    if (InputManager::getInstance().isKeyDown("right", m_playerIndex))
    {
        inputDirection.x = 1.0f;
        playerAni->changeAnimation(1);
        if (InputManager::getInstance().isKeyDown("space", m_playerIndex) && m_isDashActive)
        {
            playerAni->changeAnimation(2);
        }
    }
    else if (InputManager::getInstance().isKeyDown("left", m_playerIndex))
    {
        inputDirection.x = -1.0f;
        playerAni->changeAnimation(1);
        if (InputManager::getInstance().isKeyDown("space", m_playerIndex) && m_isDashActive)
        {
            playerAni->changeAnimation(3);
        }
    }
    if (InputManager::getInstance().isKeyDown("up", m_playerIndex))
    {
        inputDirection.y = -1.0f;
        playerAni->changeAnimation(1);
        if (InputManager::getInstance().isKeyDown("space", m_playerIndex) && m_isDashActive)
        {
            playerAni->changeAnimation(2);
        }
        else if (InputManager::getInstance().isKeyDown("space", m_playerIndex) && m_isDashActive &&
                 InputManager::getInstance().isKeyDown("right", m_playerIndex))
        {
            playerAni->changeAnimation(2);
        }
        else if (InputManager::getInstance().isKeyDown("space", m_playerIndex) && m_isDashActive &&
                 InputManager::getInstance().isKeyDown("left", m_playerIndex))
        {
            playerAni->changeAnimation(3);
        }
    }
    else if (InputManager::getInstance().isKeyDown("down", m_playerIndex))
    {
        inputDirection.y = 1.0f;
        playerAni->changeAnimation(1);
        if (InputManager::getInstance().isKeyDown("space", m_playerIndex) && m_isDashActive)
        {
            playerAni->changeAnimation(2);
        }
        else if (InputManager::getInstance().isKeyDown("space", m_playerIndex) && m_isDashActive &&
                 InputManager::getInstance().isKeyDown("right", m_playerIndex))
        {
            playerAni->changeAnimation(2);
        }
        else if (InputManager::getInstance().isKeyDown("space", m_playerIndex) && m_isDashActive &&
                 InputManager::getInstance().isKeyDown("left", m_playerIndex))
        {
            playerAni->changeAnimation(3);
        }
    }

// Check if space key is pressed and not on cooldown
    if (InputManager::getInstance().isKeyPressed("space", m_playerIndex) && !m_isDashOnCooldown)
    {
        // Start the dash
        m_isDashActive = true;
        m_dashTimer    = 0.0f;
    }

    // If dash is active, apply dash speed for its duration
    if (m_isDashActive)
    {
        translation.x += dashSpeed * inputDirection.x * deltaTime;
        translation.y += dashSpeed * inputDirection.y * deltaTime;

        // Update dash timer
        m_dashTimer += deltaTime;

        // Check if dash duration is over
        if (m_dashTimer >= m_dashDuration)
        {
            m_isDashActive = false;

            // Start cooldown
            m_isDashOnCooldown = true;
            m_cooldownTimer    = 0.0f;
        }
    }
    else
    {
        // Regular movement
        translation.x += speed * inputDirection.x * deltaTime;
        translation.y += speed * inputDirection.y * deltaTime;
    }

    // If dash is not active, update cooldown timer
    if (!m_isDashActive && m_isDashOnCooldown)
    {
        m_cooldownTimer += deltaTime;

        // Check if cooldown is over
        if (m_cooldownTimer >= m_dashCooldown)
        {
            m_isDashOnCooldown = false;
        }
    }

    // If no input, set velocity to zero to stop the player immediately
    if (translation.x == 0.0F && translation.y == 0.0F)
    {
        m_rigidBody.addVelocity(sf::Vector2f(0.0f, 0.0f));
        playerAni->changeAnimation(0);
    }

#if 1 // physics movement
    m_rigidBody.addVelocity(translation);
#else // no physics movement
    m_gameObject.GetTransform().translate(translation);
#endif
}
} // namespace mmt_gd
