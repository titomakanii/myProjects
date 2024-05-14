#pragma once

#include "IRenderComponent.hpp"

#include <SFML/Graphics.hpp>
#include <string>

namespace mmt_gd
{
class SpriteRenderComponent final : public IRenderComponent
{
public:
    using Ptr = std::shared_ptr<SpriteRenderComponent>;

    SpriteRenderComponent(GameObject& gameObject, sf::RenderWindow& renderWindow, std::string textureFile, std::string layerName);

    ~SpriteRenderComponent() override;
    
    SpriteRenderComponent(SpriteRenderComponent& other) :
    IRenderComponent(other.m_gameObject, other.m_renderWindow),
    m_textureFile(other.m_textureFile),
    m_texture(other.m_texture),
    m_sprite(m_sprite),
    m_layerName(other.m_layerName),
    m_gameObject(other.m_gameObject)
    {}

    bool init() override;

    void update(float deltaTime) override
    {
    }

    void draw() override;

    sf::Sprite& getSprite()
    {
        return m_sprite;
    }

private:
    std::string m_textureFile;
    sf::Texture m_texture;
    sf::Sprite  m_sprite;
    std::string m_layerName;
    GameObject& m_gameObject;
};
} // namespace mmt_gd
