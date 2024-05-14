#pragma once

#include "GameObject.hpp"
#include "IComponent.hpp"
#include "GameObjectManager.hpp"

#include <SFML/System/Vector2.hpp>

namespace mmt_gd
{
class EnemyMoveComponent : public IComponent
{
public:
    EnemyMoveComponent(GameObject& gameObject, GameObjectManager& gameObjectManager);

    void update(float deltaTime) override;
    bool init() override;

private:
    GameObject&         m_gameObject;
    GameObject&         m_gameObjectManager;
    float               m_moveSpeed; // Geschwindigkeit, mit der der Feind sich bewegt
};
} // namespace mmt_gd
