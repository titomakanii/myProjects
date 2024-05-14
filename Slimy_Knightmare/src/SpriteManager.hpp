#pragma once

#include "EventBus.hpp"

#include <SFML/Graphics.hpp>
#include <unordered_map>

namespace mmt_gd
{
class IRenderComponent;

class SpriteManager
{
public:
    using TileSetMap = std::unordered_map<std::string, std::shared_ptr<sf::Texture>>;

    explicit SpriteManager(sf::RenderWindow& renderWindow) : m_renderWindow(renderWindow)
    {
    }

    void init();
    void shutdown();

    void setCamera(IRenderComponent* cameraComp)
    {
        m_camera = cameraComp;
    }

    IRenderComponent* getCamera() const
    {
        return m_camera;
    }

    void addCompToLayer(const std::string& layer, IRenderComponent* comp);
    void removeComp(IRenderComponent* comp);

    std::string getLayer(const IRenderComponent* comp);

    void setLayerOrder(const std::vector<std::string>& layerOrder)
    {
        m_layerOrder = layerOrder;
    }

    void setTileSize(const sf::Vector2i& tileSize)
    {
        m_tileSize = tileSize;
    }

    sf::Vector2i getTileSize() const
    {
        return m_tileSize;
    }

    void setTileSets(const TileSetMap& tileSets)
    {
        m_tileSets = tileSets;
    }

    const TileSetMap& getTileSets() const
    {
        return m_tileSets;
    }

    sf::RenderWindow& getWindow() const
    {
        return m_renderWindow;
    }

    void draw();

private:
    sf::RenderWindow& m_renderWindow;

    sf::Vector2i m_tileSize{};
    TileSetMap   m_tileSets;

    IRenderComponent* m_camera = nullptr;

    std::map<std::string, std::list<IRenderComponent*>> m_layerToComp;
    std::map<const IRenderComponent*, std::string>      m_compToLayer;

    std::vector<std::string> m_layerOrder;

    std::list<EventBus::ListenerId> m_listeners;
};
} // namespace mmt_gd
