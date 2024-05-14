#pragma once

//#include "stdafx.h"
#include "GameObject.hpp"
#include "SpriteRenderComponent.hpp"
#include "Tileson.hpp"


namespace mmt_gd
{
class PowerUpManager
{
public:
    static PowerUpManager& getInstance();
    PowerUpManager(const PowerUpManager& rhv)             = delete;
    PowerUpManager(PowerUpManager&& rhv)                  = delete;
    PowerUpManager&  operator=(const PowerUpManager& rhv) = delete;
    PowerUpManager&& operator=(PowerUpManager&& rhv)      = delete;

    const std::vector<std::shared_ptr<GameObject>>& getActivePowerUps() const
    {
        return m_activePowerUps;
    }
    const std::pair<std::pair<int, int>, std::pair<int, int>>& getPowerUpSpawnArea() const
    {
        return m_powerUpSpawnArea;
    }

    void init();

    void shutdown();

    void spawnPowerUp();

    void setPowerUpSpawnArea(const std::pair<std::pair<int, int>, std::pair<int, int>>& area)
    {
        m_powerUpSpawnArea = area;
    }

    void addPowerUp(std::string powerUp, tson::Object object)
    {
        m_availablePowerUps.push_back(std::pair(powerUp, object));
    }

    void setRessourcePath(const fs::path& path)
    {
        m_ressourcePath = path;
    }

    void setRenderWindow(sf::RenderWindow& window)
    {
        // safe reference of the render window
        m_renderWindow = &window;
    }

    void setLayer(const std::string& layer)
    {
        m_layer = layer;
    }
    std::pair<std::pair<int, int>, std::pair<int, int>> m_powerUpSpawnArea = {{0, 0}, {0, 0}};
    std::pair<int, int>                                 m_powerUpSize      = {20, 40};
    std::vector<std::shared_ptr<GameObject>>            m_activePowerUps;

private:
    PowerUpManager()  = default;
    ~PowerUpManager() = default;

    fs::path                                            m_ressourcePath = "";
    sf::RenderWindow*                                   m_renderWindow;
    std::string                                         m_layer        = "";
    int                                                 m_powerUpIndex = 0;
    std::vector<std::pair<std::string, tson::Object>>   m_availablePowerUps;
    int                                                 m_powerUpCount     = 15;
    sf::Music										    m_sound;
};
} // namespace mmt_gd
