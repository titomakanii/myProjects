// MMP2 Project made by: Nicolas van Renen, Andrè Linder
#include "stdafx.h"

#include "EventBus.hpp"
#include "GameObject.hpp"
#include "RenderComponentEvents.hpp"
#include "AnimatedSprite.hpp"

#include <utility>

namespace mmt_gd
{
SpriteAnimationComponent::SpriteAnimationComponent(
    GameObject&       gameObject,
    sf::RenderWindow& renderWindow,
    std::string       textureFile,
    std::string       layerName,
    sf::Vector2i      Spritebox,
    float             animatonSpeed) :
IRenderComponent(gameObject, renderWindow),
m_textureFile(std::move(textureFile)),
m_layerName(std::move(layerName)),
m_spriteRowsAndCollums(Spritebox),
m_animationSpeed(animatonSpeed)


{
    EventBus::getInstance().fireEvent(std::make_shared<RenderableCreateEvent>(m_layerName, *this));
}

SpriteAnimationComponent::~SpriteAnimationComponent()
{
    EventBus::getInstance().fireEvent(std::make_shared<RenderableDestroyEvent>(m_layerName, *this));
}

bool SpriteAnimationComponent::init()
{
    sf::Image image;
    if (!image.loadFromFile(m_textureFile))
    {
        sf::err() << "Could not load texture from " << m_textureFile << std::endl;
        return false;
    }
    image.createMaskFromColor(sf::Color::Black);
    m_texture.loadFromImage(image);
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(-40, -48);
    setTextureRect();
    m_sprite.setTextureRect(textureRect);
    ColumnSizeforthisRow = m_spriteRowsAndCollums.x;

    return true;
}
void SpriteAnimationComponent::update(float deltatime)
{
    // Update the animation
    if (m_animationSpeed != 0)
    {
        time += deltatime;
    }

    if (time > m_animationSpeed)
    {
        if (singleSquaresize.x + textureRect.left >= ColumnSizeforthisRow * singleSquaresize.x)
        {
            textureRect.left = 0;
        }
        else
        {
            textureRect.left += singleSquaresize.x;
        }
        m_sprite.setTextureRect(textureRect);
        time = 0;
    }
}


void SpriteAnimationComponent::setTextureRect()
{
    singleSquaresize.x = m_texture.getSize().x / m_spriteRowsAndCollums.x;
    singleSquaresize.y = m_texture.getSize().y / m_spriteRowsAndCollums.y;
    textureRect        = sf::IntRect(currentTextureRectPosition.x,
                              currentTextureRectPosition.y,
                              singleSquaresize.x,
                              singleSquaresize.y);
}
void SpriteAnimationComponent::changeAnimation(int row)
{
    // change the row of the animation
    textureRect.top = singleSquaresize.y * row;
}
void SpriteAnimationComponent::changeAnimation(int row, int columamount)
{
    // change the row of the animation and the amount of columns
    ColumnSizeforthisRow = columamount;
    textureRect.top      = singleSquaresize.y * row;
}

void SpriteAnimationComponent::draw()
{
    m_renderWindow.draw(m_sprite, m_gameObject.getTransform());
}
} // namespace mmt_gd
