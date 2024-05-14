#include "stdafx.h"
#include "BoxCollisionComponent.hpp"
#include "GameObject.hpp"

namespace mmt_gd
{

BoxCollisionComponent::BoxCollisionComponent(GameObject& gameObject, const sf::FloatRect& rect, bool isTrigger)
    : IComponent(gameObject), m_boundingBox(rect), m_isTrigger(isTrigger){}

bool BoxCollisionComponent::init()
{
    // Initialisierungsfunktion, falls ben�tigt
    return true;
}

void BoxCollisionComponent::update(float deltaTime)
{
    // Aktualisierungsfunktion f�r die Kollisionskomponente
    // Wenn n�tig, z.B. �berpr�fung von Kollisionen

}

void BoxCollisionComponent::setBoundingBox(const sf::FloatRect& rect)
{
    m_boundingBox = rect;
}

sf::FloatRect BoxCollisionComponent::getBoundingBox() const
{
    return m_boundingBox;
}

void BoxCollisionComponent::setAsTrigger(bool isTrigger)
{
    m_isTrigger = isTrigger;
}

bool BoxCollisionComponent::isTrigger() const
{
    return m_isTrigger;
}

} // namespace mmt_gd