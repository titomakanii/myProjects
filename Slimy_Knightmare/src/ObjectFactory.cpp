// MMP2 Project made by: Nicolas van Renen, Andrè Linder
#include "stdafx.h"

#include "ObjectFactory.hpp"

#include "ColliderComponent.hpp"
#include "GameObjectEvents.hpp"
#include "PhysicsManager.hpp"
#include "PlayerMoveComponent.hpp"
#include "PointsComponent.hpp"
#include "SpriteRenderComponent.hpp"
#include "EnemyMoveComponent.hpp"
#include "Tileson.hpp"
#include "PlayerHealthComponent.hpp"
#include "AnimatedSprite.hpp"
#include "AIMovementComponent.hpp"
#include "PowerUpManager.hpp"




namespace mmt_gd
{
static GameObject::Ptr loadSprite(tson::Object&        object,
                                  const std::string&   layer,
                                  const fs::path&      resourcePath,
                                  const SpriteManager& spriteManager)
{
    auto gameObject = GameObject::create(object.getName());

    gameObject->setPosition(static_cast<float>(object.getPosition().x), static_cast<float>(object.getPosition().y));

    // Parse data from file
    sf::IntRect textureRect{};
    textureRect.width  = object.getSize().x;
    textureRect.height = object.getSize().y;
    fs::path spriteTexture;
    sf::Vector2i RowsAndCollums(1, 1);
    float        animationSpeed;
    auto     input     = false;
    auto     enemy     = false;
    auto     playerIdx = 0;
    auto     playerh   = 60;
    auto     enemyIdx = 0;


    for (const auto* property : object.getProperties().get())
    {
        if (auto name = property->getName(); name == "Texture")
        {
            spriteTexture = resourcePath / std::any_cast<std::string>(property->getValue());
        }
        else if (name == "TextureRectLeft")
        {
            textureRect.left = std::any_cast<int>(property->getValue());
        }
        else if (name == "TextureRectTop")
        {
            textureRect.top = std::any_cast<int>(property->getValue());
        }
        else if (name == "InputPlayerIdx")
        {
            input     = true;
            playerIdx = std::any_cast<int>(property->getValue());
        }
        else if (name == "InputEnemyIdx")
        {
            input    = false;
            enemy   = true;
            enemyIdx = std::any_cast<int>(property->getValue());
        }
        else if (name == "Rows")
        {
            RowsAndCollums.y = std::any_cast<int>(property->getValue());
        }
        else if (name == "Columns")
        {
            RowsAndCollums.x = std::any_cast<int>(property->getValue());
        }
        else if (name == "AnimationSpeed")
        {
            animationSpeed = std::any_cast<float>(property->getValue());
        }
        else if (name == "Mass")
        {
            auto mass = std::any_cast<float>(property->getValue());
        }
    }

    if (spriteTexture.string().length() > 0)
    {
        const auto renderComp = gameObject->addComponent<SpriteAnimationComponent>(*gameObject,
                                                                                   spriteManager.getWindow(),
                                                                                   spriteTexture.string(),
                                                                                   layer,
                                                                                   RowsAndCollums,
                                                                                   animationSpeed);

        renderComp->getSprite().setTextureRect(textureRect);
    }


    const auto rigidComp = gameObject->addComponent<RigidBodyComponent>(*gameObject, b2_dynamicBody);
    rigidComp->getB2Body()->SetFixedRotation(true);
    b2PolygonShape polygonShape;
    const auto     size = PhysicsManager::t2b(object.getSize(), true);
    polygonShape.SetAsBox(size.x / 2, size.y / 2, b2Vec2{size.x / 2, size.y / 2}, 0);
    b2FixtureDef fixtureDef{};
    fixtureDef.shape   = &polygonShape;
    fixtureDef.density = 1;

    gameObject->addComponent<ColliderComponent>(*gameObject, *rigidComp, fixtureDef);

    if (enemy)
    {
        gameObject->addComponent<AIMovementComponent>(*gameObject, *rigidComp, enemyIdx);
    }
    if (input)
    {
        gameObject->addComponent<PlayerMoveComponent>(*gameObject, *rigidComp, playerIdx);
        gameObject->addComponent<HealthComponent>(*gameObject, 100);
        gameObject->addComponent<PointsComponent>(*gameObject, 0); // Hinzufügen der PointsComponent
    }

    if (!gameObject->init())
    {
        sf::err() << "Could not initialize go " << gameObject->getId() << " in TileMap " << std::endl;
    }

    EventBus::getInstance().fireEvent(std::make_shared<GameObjectCreateEvent>(gameObject));

    return gameObject;
}

static GameObject::Ptr loadCollider(const tson::Object& object, const std::string& layer)
{
    auto gameObject = GameObject::create(object.getName());
    gameObject->setPosition(static_cast<float>(object.getPosition().x), static_cast<float>(object.getPosition().y));

    const auto rigidComp = gameObject->addComponent<RigidBodyComponent>(*gameObject, b2_staticBody);

    b2PolygonShape polygonShape{};
    const auto     size = PhysicsManager::t2b(object.getSize());
    polygonShape.SetAsBox(size.x / 2, size.y / 2, b2Vec2{size.x / 2, size.y / 2}, 0);

    b2FixtureDef fixtureDef{};
    fixtureDef.shape = &polygonShape;

    gameObject->addComponent<ColliderComponent>(*gameObject, *rigidComp, fixtureDef);

    if (!gameObject->init())
    {
        sf::err() << "Could not initialize go " << gameObject->getId() << " in TileMap " << std::endl;
    }

    EventBus::getInstance().fireEvent(std::make_shared<GameObjectCreateEvent>(gameObject));

    return gameObject;
}

static GameObject::Ptr loadTrigger(tson::Object&        object,
                                   const std::string&   layer,
                                   const fs::path&      resourcePath,
                                   const SpriteManager& spriteManager)
{
    auto gameObject = GameObject::create(object.getName());
    gameObject->setPosition(static_cast<float>(object.getPosition().x), static_cast<float>(object.getPosition().y));

     sf::IntRect textureRect{};
        textureRect.width  = object.getSize().x;
        textureRect.height = object.getSize().y;
        fs::path spriteTexture;

        for (const auto* property : object.getProperties().get())
        {
            if (auto name = property->getName(); name == "Texture")
            {
                spriteTexture = resourcePath / std::any_cast<std::string>(property->getValue());
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


        auto renderComp = gameObject->addComponent<SpriteRenderComponent>(*gameObject,
                                                                          spriteManager.getWindow(),
                                                                          spriteTexture.string(),
                                                                          layer);
        renderComp->getSprite().setTextureRect(textureRect);

    const auto rb = gameObject->addComponent<RigidBodyComponent>(*gameObject, b2_staticBody);

    b2PolygonShape polygonShape{};
    const auto     size = PhysicsManager::t2b(object.getSize());
    polygonShape.SetAsBox(size.x / 2, size.y / 2, b2Vec2{size.x / 2, size.y / 2}, 0);


    b2FixtureDef fixtureDef{};
    fixtureDef.shape    = &polygonShape;
    fixtureDef.isSensor = true;

    gameObject->addComponent<ColliderComponent>(*gameObject, *rb, fixtureDef);


    if (!gameObject->init())
    {
        sf::err() << "Could not initialize go " << gameObject->getId() << " in TileMap " << std::endl;
    }

    EventBus::getInstance().fireEvent(std::make_shared<GameObjectCreateEvent>(gameObject));

    return gameObject;
}
static void loadPowerup(tson::Object& object, const std::string& layer, const fs::path& path, const SpriteManager& spriteManager)
{
    PowerUpManager& powerUpManager = PowerUpManager::getInstance();

    powerUpManager.setRessourcePath(path);
    powerUpManager.setRenderWindow(spriteManager.getWindow());
    powerUpManager.setLayer(layer);

    powerUpManager.addPowerUp(object.getName(), object);
}
GameObject::Ptr ObjectFactory::processTsonObject(tson::Object&        object,
                                                 const tson::Layer&   layer,
                                                 const fs::path&      path,
                                                 const SpriteManager& spriteManager)
{
    if (object.getType() == "Sprite")
    {
        auto sprite = loadSprite(object, layer.getName(), path, spriteManager);
    }
    if (object.getType() == "Collider")
    {
        auto collider = loadCollider(object, layer.getName());
    }
    if (object.getName() == "Trigger")
    {
        auto cakeObject = loadTrigger(object, layer.getName(), path, spriteManager);
    }
    if (object.getType() == "Powerup")
    {
        loadPowerup(object, layer.getName(), path, spriteManager);
    }


    return {};
}
} // namespace mmt_gd
