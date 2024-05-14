// MMP2 Project made by: Nicolas van Renen, Andrè Linder
#include "stdafx.h"

#include "CameraRenderComponent.hpp"

#include "GameObject.hpp"

namespace mmt_gd
{
CameraRenderComponent::CameraRenderComponent(GameObject& gameObject, sf::RenderWindow& renderWindow, sf::View view) :
IRenderComponent(gameObject, renderWindow),
m_view(view)
{
}

bool CameraRenderComponent::init()
{
    return true;
}

void CameraRenderComponent::draw()
{
}

void CameraRenderComponent::update(float deltaTime)
{
    float tiledMapWidth = 100;
    float tiledMapHeight = 50;
    float tiledMapTileSize = 32;
    float mapWidth  = tiledMapWidth * tiledMapTileSize;
    float mapHeight = tiledMapHeight * tiledMapTileSize;


    // Define the size of the view
    float viewWidth  = m_renderWindow.getView().getSize().x;
    float viewHeight = m_renderWindow.getView().getSize().y;
    float maxX       = mapWidth - viewWidth / 2.0f;
    float maxY       = mapHeight - viewHeight / 2.0f;

    // get the position of the player
    sf::Vector2f playerPosition = m_gameObject.getPosition();

    // set the limits of the view
    float viewX = std::max(viewWidth / 2.0f, std::min(playerPosition.x, maxX));
    float viewY = std::max(viewHeight / 2.0f, std::min(playerPosition.y, maxY));

    m_view.setCenter(viewX, viewY);

    m_renderWindow.setView(m_view);
}
} // namespace mmt_gd
