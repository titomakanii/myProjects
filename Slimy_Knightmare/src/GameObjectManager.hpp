#pragma once

#include "EventBus.hpp"
#include "GameObject.hpp"

#include <string>
#include <set>
#include <memory>

namespace mmt_gd
{
class GameObjectManager
{
public:
    using GameObjectMap = std::set<GameObject::Ptr>;

    static GameObjectManager& getInstance()
    {
        static GameObjectManager instance;
        return instance;
    }

    void init();
    void shutdown();
    void update(float deltaTime);

    void            addGameObject(const GameObject::Ptr& gameObject);
    GameObject::Ptr getGameObject(const std::string& id) const;

    GameObjectMap& getGameObjects()
    {
        return m_gameObjects;
    }

    void removeGameObject(const std::shared_ptr<GameObject>& go);

private:
    GameObjectMap m_gameObjects;

    std::list<EventBus::ListenerId> m_listeners;
};
} // namespace mmt_gd
