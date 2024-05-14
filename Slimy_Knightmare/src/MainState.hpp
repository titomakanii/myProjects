#pragma once

#include "GameObjectManager.hpp"
#include "GameState.hpp"
#include "PhysicsManager.hpp"
#include "SpriteManager.hpp"
#include "AnimatedSprite.hpp"


namespace mmt_gd
{
class FINALFRONTIER_API MainState final : public GameState
{
public:
    MainState(GameStateManager* gameStateManager, Game* game);

    void init() override;
    void exit() override;

    void update(float deltaTime) override;
    void draw() override;
    int  getYourScore() const;
    void  addPoints(int points);
    float m_elapsedTime;
    void  updatePowerUpPositions();


private:
    float                         m_powerUpTimer;
    sf::Text                      m_text;
    sf::Font                      m_font;
    sf::View                      m_view;
    sf::Music                     m_music;
    SpriteManager     m_spriteManager;
    GameObjectManager m_gameObjectManager;
    PhysicsManager    m_physicsManager;
    sf::Vector2f                  lastPlayerPosition;
    int                           yourScore;
    void                          drawPoints();

    void drawDashCooldownCircle();

    void savePointsToHighscoreFile(const std::string& filename, int points);
    void saveCurrentScoreToFile(const std::string& filename) const;
    void loadHighscoresFromFile(const std::string& filename);
    void addScoreToHighscores(int score);
    void displayHighscores();

    std::vector<int> highscores;
};
} // namespace mmt_gd
