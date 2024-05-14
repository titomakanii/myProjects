#pragma once

#include "GameObject.hpp"

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

namespace mmt_gd
{
class EnemyPool
{
public:
    EnemyPool(size_t             size,
              const std::string& textureFile,
              sf::IntRect        textureRect,
              const std::string& layerName,
              sf::RenderWindow&  renderWindow,
              sf::FloatRect      colliderRect,
              float              mass);
    GameObject::Ptr getEnemy();

private:
    std::vector<GameObject::Ptr> m_pool;
    size_t                       m_counter = 0;
};
} // namespace mmt_gd