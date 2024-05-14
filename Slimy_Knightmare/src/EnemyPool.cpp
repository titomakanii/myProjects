#include "stdafx.h"
#include "EnemyPool.hpp"
#include "ColliderComponent.hpp"
#include "EventBus.hpp"
#include "GameObjectEvents.hpp"
#include "PhysicsManager.hpp"
#include "RigidBodyComponent.hpp"
#include "SpriteRenderComponent.hpp"

#include <iostream>
#include <memory>

namespace mmt_gd
{
EnemyPool::EnemyPool(size_t             size,
                     const std::string& textureFile,
                     sf::IntRect        textureRect,
                     const std::string& layerName,
                     sf::RenderWindow&  renderWindow,
                     sf::FloatRect      colliderRect,
                     float              mass)
{
    m_pool.reserve(size);
    for (size_t i = 0; i < size; ++i)
    {
        auto gameObject = std::make_shared<GameObject>("Enemy_" + std::to_string(i));
        gameObject->setPosition(-1000, -1000);

        const auto renderComp = gameObject->addComponent<SpriteRenderComponent>(*gameObject, renderWindow, textureFile, layerName);
        renderComp->getSprite().setTextureRect(textureRect);

        auto rigidBodyComponent = gameObject->addComponent<RigidBodyComponent>(*gameObject, b2_dynamicBody);

        auto fixtureDef    = b2FixtureDef{};
        fixtureDef.density = mass;

        auto shape        = b2PolygonShape{};
        auto spriteBounds = renderComp->getSprite().getGlobalBounds();
        shape.SetAsBox(spriteBounds.width * 0.5f * PhysicsManager::UNRATIO,
                       spriteBounds.height * 0.5f * PhysicsManager::UNRATIO,
                       b2Vec2{spriteBounds.width * 0.5f * PhysicsManager::UNRATIO,
                              spriteBounds.height * 0.5f * PhysicsManager::UNRATIO},
                       0);
        fixtureDef.shape = &shape;

        auto colliderComponent = gameObject->addComponent<ColliderComponent>(*gameObject, *rigidBodyComponent, fixtureDef);

        if (!gameObject->init())
        {
            sf::err() << "Could not initialize game object " << gameObject->getId() << std::endl;
        }

        rigidBodyComponent->getB2Body()->SetEnabled(false);
        gameObject->setActive(false);

        m_pool.push_back(gameObject);
    }
}

GameObject::Ptr EnemyPool::getEnemy()
{
    return m_pool[m_counter++ % m_pool.size()];
}
} // namespace mmt_gd