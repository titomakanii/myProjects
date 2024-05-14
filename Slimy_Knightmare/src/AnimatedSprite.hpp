#pragma once

#include "IRenderComponent.hpp"

#include <SFML/Graphics.hpp>
#include <string>

namespace mmt_gd
{
class SpriteAnimationComponent final : public IRenderComponent
{
public:
    using Ptr = std::shared_ptr<SpriteAnimationComponent>;

    SpriteAnimationComponent(GameObject&       gameObject,
                             sf::RenderWindow& renderWindow,
                             std::string       textureFile,
                             std::string       layerName,
                             sf::Vector2i      spriteRowsAndCollums,
                             float             animationSpeed);


    ~SpriteAnimationComponent() override;

    bool init() override;

    void update(float deltaTime) override;

    void draw() override;
    /// <summary>
    /// changes row so that the animation can play in a different animation
    /// </summary>
    /// <param name="row"></param>
    void changeAnimation(int row);
    void changeAnimation(int row, int columAmount);


    sf::Sprite& getSprite()
    {
        return m_sprite;
    }

private:
    void        setTextureRect();
    std::string m_textureFile;
    sf::Texture m_texture;
    sf::Sprite  m_sprite;
    std::string m_layerName;

    /// <summary>
    /// how many rows and collums the texture has
    /// </summary>
    sf::Vector2i m_spriteRowsAndCollums;
    float        m_animationSpeed;
    sf::Vector2f singleSquaresize;
    sf::Vector2f currentTextureRectPosition = sf::Vector2f(0.f, 0.f);
    sf::IntRect  textureRect;
    float        time = 0;
    /// <summary>
    /// Can be changed when you switch animations
    /// </summary>
    int ColumnSizeforthisRow;
};
} // namespace mmt_gd
