#pragma once

#include "IComponent.hpp"

#include <SFML/Graphics/Rect.hpp>

namespace mmt_gd
{

class BoxCollisionComponent : public IComponent
{
public:
    BoxCollisionComponent(GameObject& gameObject, const sf::FloatRect& rect, bool isTrigger);

    bool init() override;
    void update(float deltaTime) override;

    void setBoundingBox(const sf::FloatRect& rect);
    sf::FloatRect getBoundingBox() const;

    void setAsTrigger(bool isTrigger);
    bool isTrigger() const;

private:
    sf::FloatRect m_boundingBox;
    bool m_isTrigger;
};

} // namespace mmt_gd
