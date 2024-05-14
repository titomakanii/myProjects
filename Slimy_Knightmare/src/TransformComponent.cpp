// MMP2 Project made by: Nicolas van Renen, Andrè Linder
#include "stdafx.h"
#include "TransformComponent.hpp"

namespace mmt_gd
{
TransformComponent::TransformComponent(GameObject& gameObject) :
IComponent(gameObject),
m_position(0.f, 0.f),
m_rotation(0.f),
m_scale(1.f, 1.f)
{
}

void TransformComponent::setPosition(const sf::Vector2f& position)
{
    m_position = position;
}

sf::Vector2f TransformComponent::getPosition() const
{
    return m_position;
}

void TransformComponent::setRotation(float angle)
{
    m_rotation = angle;
}

float TransformComponent::getRotation() const
{
    return m_rotation;
}

void TransformComponent::setScale(const sf::Vector2f& scale)
{
    m_scale = scale;
}

sf::Vector2f TransformComponent::getScale() const
{
    return m_scale;
}
} // namespace mmt_gd
