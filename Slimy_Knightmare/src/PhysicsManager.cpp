// MMP2 Project made by: Nicolas van Renen, Andrè Linder
#include "stdafx.h"

#include "PhysicsManager.hpp"

#include "ColliderComponent.hpp"
#include "GameObjectManager.hpp"
#include "PhysicsComponentEvents.hpp"
#include "RigidBodyComponent.hpp"
#include "SpriteRenderComponent.hpp"

#include <Box2D/box2d.h>

namespace mmt_gd
{
const float PhysicsManager::RATIO(30.0F);
const float PhysicsManager::UNRATIO(1.F / RATIO);

std::shared_ptr<b2World> PhysicsManager::m_world = std::make_shared<b2World>(b2Vec2(0.F, 9.8F / 200.F)); //~0 gravity

void PhysicsManager::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
}

void PhysicsManager::BeginContact(b2Contact* contact)
{
    auto* const colliderA = reinterpret_cast<ColliderComponent*>(contact->GetFixtureA()->GetUserData().pointer);
    auto* const colliderB = reinterpret_cast<ColliderComponent*>(contact->GetFixtureB()->GetUserData().pointer);
    if (colliderA != nullptr && colliderB != nullptr)
    {
        if (colliderA->getGameObject().getParentId() == colliderB->getGameObject().getId() ||
            colliderB->getGameObject().getParentId() == colliderA->getGameObject().getId())
        {
            return;
        }
        colliderA->onCollision(*colliderB);
        colliderB->onCollision(*colliderA);
    }
}

void PhysicsManager::EndContact(b2Contact* contact)
{
}


void PhysicsManager::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
}

void PhysicsManager::init()
{
    m_world->SetContactListener(this);
    // subscribe to events to catch creation events of physics objects
    {
        const auto id = EventBus::getInstance()
                            .addListener(RigidBodyCreateEvent::m_eventType,
                                         [this](const IEvent::Ptr& event)
                                         {
                                             const auto rigidbodyEvent = std::static_pointer_cast<RigidBodyCreateEvent>(
                                                 event);
                                             m_rbodies.push_back(&rigidbodyEvent->getData());
                                         });
        m_listeners.push_back(id);
    }
    // subscribe to events to catch creation events of physics objects
    {
        const auto id = EventBus::getInstance()
                            .addListener(RigidBodyDestroyEvent::m_eventType,
                                         [this](const IEvent::Ptr& event)
                                         {
                                             const auto rigidbodyEvent = std::static_pointer_cast<RigidBodyDestroyEvent>(
                                                 event);

                                             const auto it = std::find(m_rbodies.begin(),
                                                                       m_rbodies.end(),
                                                                       &rigidbodyEvent->getData());

                                             if (it != m_rbodies.end())
                                             {
                                                 PhysicsManager::destroyB2Body(*rigidbodyEvent->getData().getB2Body());

                                                 m_rbodies.erase(it);
                                             }
                                         });
        m_listeners.push_back(id);
    }
}

void PhysicsManager::shutdown()
{
    for (auto it = m_listeners.begin(); it != m_listeners.end(); ++it)
    {
        EventBus::getInstance().removeListener(*it);
    }

    performTasks();
    m_listeners.clear();
    m_rbodies.clear();
}

void PhysicsManager::update(const float deltaTime)
{
    m_world->Step(deltaTime, 8, 3);
    performTasks();


    for (auto i = 0; i < m_rbodies.size(); ++i)
    {
        if (m_rbodies.at(i)->getB2Body() == nullptr)
        {
            m_rbodies.erase(m_rbodies.begin() + i--);
            continue;
        }
        m_rbodies.at(i)->physicsUpdate(deltaTime);
    }
}

std::shared_ptr<b2World> PhysicsManager::get_b2_world()
{
    return m_world;
}

b2Body* PhysicsManager::createB2Body(b2BodyDef& def)
{
    return m_world->CreateBody(&def);
}

void PhysicsManager::destroyB2Body(b2Body& def)
{
    queueTask([&def]() { 
        PhysicsManager::get_b2_world()->DestroyBody(&def);
        });
}
void PhysicsManager::moveB2Body(b2Body& body, const sf::Vector2f& position, float angle)
{
    queueTask([&body, &position, angle]() { body.SetTransform(s2b(position), angle); });
}

void PhysicsManager::performTasks()
{
    for (auto& task : tasks)
    {
        task();
    }
    tasks.clear();
}

void PhysicsManager::queueTask(std::function<void()> task)
{
    tasks.push_back(task);
}

std::vector<std::function<void()>> mmt_gd::PhysicsManager::tasks;


b2Vec2 PhysicsManager::s2b(const sf::Vector2f& vec, const bool scale)
{
    return scale ? b2Vec2(vec.x * UNRATIO, vec.y * UNRATIO) : b2Vec2(vec.x, vec.y);
}

sf::Vector2f PhysicsManager::b2s(const b2Vec2& vec, const bool scale)
{
    return scale ? sf::Vector2f(vec.x, vec.y) * RATIO : sf::Vector2f(vec.x, vec.y);
}

b2Vec2 PhysicsManager::t2b(const tson::Vector2i& vec, const bool scale)
{
    return scale ? b2Vec2(vec.x * UNRATIO, vec.y * UNRATIO) : b2Vec2(vec.x, vec.y);
}

b2Vec2 PhysicsManager::t2b(const tson::Vector2f& vec, bool scale)
{
    return scale ? b2Vec2(vec.x * UNRATIO, vec.y * UNRATIO) : b2Vec2(vec.x, vec.y);
}

tson::Vector2f PhysicsManager::b2t(const b2Vec2& vec, bool scale)
{
    return scale ? tson::Vector2f(vec.x * RATIO, vec.y * RATIO) : tson::Vector2f(vec.x, vec.y);
}

sf::Color PhysicsManager::b2s(const b2Color& color, const int alpha)
{
    return {static_cast<sf::Uint8>(color.r * 255),
            static_cast<sf::Uint8>(color.g * 255),
            static_cast<sf::Uint8>(color.b * 255),
            static_cast<sf::Uint8>(alpha)};
}

b2Color PhysicsManager::s2b(const sf::Color& color, const int alpha)
{
    return {color.r / 255.0F, color.g / 255.0F, color.b / 255.0F, color.a / 255.0F};
}
} // namespace mmt_gd
