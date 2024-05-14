#include "stdafx.h"

#include "EnemyMoveComponent.hpp"

#include <cmath>

namespace mmt_gd
{
EnemyMoveComponent::EnemyMoveComponent(GameObject& gameObject, GameObjectManager& gameObjectManager) :
IComponent(gameObject),
m_gameObject(gameObject),
m_gameObjectManager(gameObjectManager),
m_moveSpeed(500.0f) // Geschwindigkeit anpassen
{
}

bool EnemyMoveComponent::init()
{
    // Initialisierungscode hier, falls benötigt
    return true;
}

void EnemyMoveComponent::update(float deltaTime)
{
    // Erhalten Sie das Spielerobjekt mit dem Namen "Player0"
    auto player = m_gameObjectManager.getGameObject("Player0");
    if (player == nullptr)
    {
        // Spieler "Player0" wurde nicht gefunden, daher kann der Gegner nicht bewegt werden
        return;
    }

    // Erhalten Sie die Position des Spielers
    sf::Vector2f playerPosition = player->getPosition();

    // Erhalten Sie die Position des Gegners
    sf::Vector2f enemyPosition = m_gameObject.getPosition();

    // Berechnen Sie die Richtung vom Gegner zum Spieler
    sf::Vector2f direction = playerPosition - enemyPosition;

    // Berechnen Sie die Entfernung zwischen Spieler und Gegner
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    // Normalisieren Sie die Richtung, um eine Einheitsvektor zu erhalten
    if (distance != 0)
    {
        direction /= distance;
    }

    // Bewegen Sie den Gegner in Richtung des Spielers mit der festgelegten Geschwindigkeit
    sf::Vector2f movement = direction * m_moveSpeed * deltaTime;

    // Bewegen Sie den Gegner
    m_gameObject.setPosition(m_gameObject.getPosition() + movement);
}
} // namespace mmt_gd


