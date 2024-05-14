#pragma once

#include "GameState.hpp"

#include <SFML/Graphics/Text.hpp>

namespace mmt_gd
{
class EndState final : public GameState
{
public:
    using GameState::GameState;

    void init() override;

    void update(float delta) override;
    void draw() override;
    void exit() override;

private:
    sf::Text    m_text;
    sf::Text    m_text2;
    sf::Text	m_scoreText;
    sf::Text    m_highscoreText;
    sf::Font    m_font;
    sf::Music   m_music;
    sf::View    m_view;
    sf::Texture m_backgroundTexture;
    sf::Sprite  m_backgroundSprite;
    int         yourScore;

    int m_highscore = 0;

    // Load highscores from a file
    void loadHighscoresFromFile(const std::string& filename);
    void loadScoreFromFile(const std::string& filename);
    
    // Vector to store highscores
    std::vector<int> highscores;

    bool m_isInit = false;
};
} // namespace mmt_gd
