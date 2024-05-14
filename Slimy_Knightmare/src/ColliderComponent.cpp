// MMP2 Project made by: Nicolas van Renen, Andrè Linder
#include "stdafx.h"

#include "ColliderComponent.hpp"

#include "DebugDraw.hpp"
#include "EventBus.hpp"
#include "GameObject.hpp"
#include "PhysicsComponentEvents.hpp"
#include "PlayerHealthComponent.hpp"

namespace mmt_gd
{
ColliderComponent::ColliderComponent(GameObject& gameObject, RigidBodyComponent& body, b2FixtureDef& def) :
IComponent(gameObject),
m_body(body),
m_fixture(nullptr)
{
    def.userData.pointer = reinterpret_cast<uintptr_t>(this);
    m_fixture            = m_body.getB2Body()->CreateFixture(&def);
}

void ColliderComponent::update(float deltaTime)
{

}

void ColliderComponent::registerOnCollisionFunction(const OnCollisionFunction& func)
{
    m_onCollisionFunctions.push_back(func);
}

void ColliderComponent::onCollision(ColliderComponent& collider)
{

    for (const auto& f : m_onCollisionFunctions)
    {
        f(*this, collider);
    }

    // Check if the collider belongs to an enemy (assuming the ID contains "Enemy")
    if (collider.m_gameObject.getId().find("Enemy") != std::string::npos)
    {
        auto playerHealthComponent = m_gameObject.getComponent<HealthComponent>();

        if (playerHealthComponent)
        {
            playerHealthComponent->reduceHealth(25);
            //std::cout << "Player collided with an enemy! Health reduced by 25. Current health: "
            //          << playerHealthComponent->getHealth() << std::endl;
        }
    }
}
} // namespace mmt_gd
