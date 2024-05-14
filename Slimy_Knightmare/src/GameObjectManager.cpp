// MMP2 Project made by: Nicolas van Renen, Andrè Linder
#include "stdafx.h"

#include "GameObjectManager.hpp"

#include "Debug.hpp"
#include "GameObjectEvents.hpp"

namespace mmt_gd
{
void GameObjectManager::init()
{
    // subscribe to creation events
    {
        const EventBus::ListenerId
            id = EventBus::getInstance()
                     .addListener(GameObjectCreateEvent::Type,
                                  [this](const IEvent::Ptr& event)
                                  {
                                      const auto goCreateEvent = std::static_pointer_cast<GameObjectCreateEvent>(event);
                                      this->addGameObject(goCreateEvent->getData());
                                  });
        m_listeners.push_back(id);
    }
}

void GameObjectManager::shutdown()
{
    m_gameObjects.clear();

    // unsubscribe from events
    for (const auto& listener : m_listeners)
    {
        EventBus::getInstance().removeListener(listener);
    }
    m_listeners.clear();
}

void GameObjectManager::update(const float deltaTime)
{
    PROFILE_FUNCTION();
    std::set<GameObject::Ptr> gameObjectsToDelete{};

     for (auto& go : m_gameObjects)
    {
        if (go->isMarkedForDelete())
        {
            gameObjectsToDelete.insert(go);
        }
        else if (go->isActive())
        {
            go->update(deltaTime);
        }
    }
    for (auto& go : gameObjectsToDelete)
    {
        removeGameObject(go);
    }
}

void GameObjectManager::addGameObject(const GameObject::Ptr& gameObject)
{
    m_gameObjects.insert(gameObject);
}

GameObject::Ptr GameObjectManager::getGameObject(const std::string& id) const
{
    for (const auto& go : m_gameObjects)
    {
        if (go->getId() == id)
        {
            return go;
        }
    }
    return nullptr;
}

void GameObjectManager::removeGameObject(const std::shared_ptr<GameObject>& go)
{
    m_gameObjects.erase(go);
}
} // namespace mmt_gd
