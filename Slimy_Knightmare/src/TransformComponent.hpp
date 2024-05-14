#pragma once

#include "IComponent.hpp"

#include <SFML/Graphics.hpp>

namespace mmt_gd
{
class TransformComponent : public IComponent
{
public:
    TransformComponent(GameObject& gameObject);

    // Getter and Setter for Position
    void         setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;

    // Getter and Setter for Rotation
    void  setRotation(float angle);
    float getRotation() const;

    // Getter and Setter for Scale
    void         setScale(const sf::Vector2f& scale);
    sf::Vector2f getScale() const;

private:
    sf::Vector2f m_position;
    float        m_rotation;
    sf::Vector2f m_scale;
};
} // namespace mmt_gd