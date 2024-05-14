// MMP2 Project made by: Nicolas van Renen, Andrè Linder
// Music is copyrightfree and no author is required
#include "stdafx.h"

#include "PowerUpManager.hpp"

#include "ColliderComponent.hpp"
#include "GameObjectEvents.hpp"
#include "HealthPowerUpComponent.hpp"
#include "PointsComponent2.hpp"
#include "PhysicsManager.hpp"
#include "RigidBodyComponent.hpp"
#include <random>
#include "PointsComponent.hpp"

namespace mmt_gd
{
class IPowerUpComponent;

PowerUpManager& PowerUpManager::getInstance()
{
    static PowerUpManager instance;
    return instance;
}

void PowerUpManager::init()
{
    for (int i = 0; i < m_powerUpCount; i++)
    {
        spawnPowerUp();
    }
}

void PowerUpManager::spawnPowerUp()
{
    // Create a random power-up
    std::random_device rd;
    std::mt19937       gen(rd());

    std::uniform_int_distribution<> dis(0, m_availablePowerUps.size() - 1);
    auto                            powerup = m_availablePowerUps[dis(gen)];

    auto object = powerup.second;

    auto gameObject = GameObject::create(powerup.first + std::to_string(m_powerUpIndex));

    const auto rb = gameObject->addComponent<RigidBodyComponent>(*gameObject, b2_staticBody);

    b2PolygonShape polygonShape{};
    const auto     size = PhysicsManager::t2b(object.getSize());
    polygonShape.SetAsBox(size.x / 2, size.y / 2, b2Vec2{size.x / 2, size.y / 2}, 0);

    // Create a fixture definition
    b2FixtureDef fixtureDef{};
    fixtureDef.shape    = &polygonShape;
    fixtureDef.isSensor = true;

    if (powerup.first == "Health")
    {
        gameObject->addComponent<HealthPowerUpComponent>(*gameObject);
    }
    else if (powerup.first == "Speed")
    {
        gameObject->addComponent<SpeedPowerUpComponent>(*gameObject);
    }

    auto collider = gameObject->addComponent<ColliderComponent>(*gameObject, *rb, fixtureDef);

    // Register the on collision function
   collider->registerOnCollisionFunction(
        [gameObject, this](ColliderComponent& a, ColliderComponent& b)
        {
            if (b.getGameObject().getId() == "Player0")
            {
                gameObject->getComponent<IPowerUpComponent>()->applyPowerUp(b.getGameObject());

                // Check if the collected power-up is PowerUp2
                if (gameObject->getComponent<SpeedPowerUpComponent>())
                {
                    // Add 10 points if PowerUp2 is collected
                    auto playerPointsComponent = b.getGameObject().getComponent<PointsComponent>();
                    if (playerPointsComponent)
                    {
                        playerPointsComponent->addPoints(10);
                        if (!m_sound.openFromFile("../assets/Musik/Pickup.ogg"))
                        {
                            std::cerr << "Failed to load music file" << std::endl;
                        }
                        else
                        {
                            m_sound.play();
                        }
                    }
                }
                
                
            std::random_device rd;
            std::mt19937       gen(rd());

            std::uniform_int_distribution<> dis(0, m_availablePowerUps.size() - 1);
            std::uniform_int_distribution<> disX(m_powerUpSpawnArea.first.first, m_powerUpSpawnArea.second.first);
            std::uniform_int_distribution<> disY(m_powerUpSpawnArea.first.second, m_powerUpSpawnArea.second.second);

            gameObject->setPosition(sf::Vector2f(disX(gen), disY(gen)));

            auto rigidBody = gameObject->getComponent<RigidBodyComponent>();


            PhysicsManager::moveB2Body(*rigidBody->getB2Body(), gameObject->getPosition(), 0);
            }
        });

    sf::IntRect textureRect{};
    textureRect.width  = object.getSize().x;
    textureRect.height = object.getSize().y;
    fs::path spriteTexture;

    // Get the texture and texture rect from the object properties
    for (const auto* property : object.getProperties().get())
    {
        if (auto name = property->getName(); name == "Texture")
        {
            spriteTexture = m_ressourcePath / std::any_cast<std::string>(property->getValue());
        }
        else if (name == "TextureRectLeft")
        {
            textureRect.left = std::any_cast<int>(property->getValue());
        }
        else if (name == "TextureRectTop")
        {
            textureRect.top = std::any_cast<int>(property->getValue());
        }
    }

    // Add a sprite render component to the game object
    auto renderComp = gameObject->addComponent<SpriteRenderComponent>(*gameObject, *m_renderWindow, spriteTexture.string(), m_layer);
    renderComp->getSprite().setTextureRect(textureRect);

    // Set the position of the game object
    std::uniform_int_distribution<> disX(m_powerUpSpawnArea.first.first, m_powerUpSpawnArea.second.first);
    std::uniform_int_distribution<> disY(m_powerUpSpawnArea.first.second, m_powerUpSpawnArea.second.second);

    gameObject->setPosition(sf::Vector2f(disX(gen), disY(gen)));

    auto rigidBody = gameObject->getComponent<RigidBodyComponent>();
    rigidBody->getB2Body()->SetTransform(PhysicsManager::s2b(gameObject->getPosition()), 0);

    gameObject->setActive(true);
    //std::cout << "PowerUpManager::init() - powerUp position: " << gameObject->getPosition().x << ", "
    //          << gameObject->getPosition().y << std::endl;

    if (!gameObject->init())
    {
        sf::err() << "Could not initialize go " << gameObject->getId() << " in TileMap " << std::endl;
    }

    m_activePowerUps.push_back(gameObject);

    EventBus::getInstance().fireEvent(std::make_shared<GameObjectCreateEvent>(gameObject));

    m_powerUpIndex++;
}
void PowerUpManager::shutdown()
{
    for (auto& powerUp : m_activePowerUps)
    {
        powerUp->setActive(false);
    }

    // clear the active power-ups
    m_activePowerUps.clear();
}


} // namespace mmt_gd