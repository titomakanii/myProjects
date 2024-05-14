// MMP2 Project made by: Nicolas van Renen, Andrè Linder
// Music is copyrightfree and no author is required
#include "stdafx.h"
#include "EndState.hpp"

#include "Game.hpp"
#include "GameStateManager.hpp"
#include "MainState.hpp"
#include "InputManager.hpp"
#include "TGUI/TGUI.hpp"


namespace mmt_gd
{
using namespace std;

void EndState::init()
{
    PROFILE_FUNCTION();

    highscores.clear();

    loadHighscoresFromFile("highscores.txt");
    loadScoreFromFile("score.txt");

    if (m_isInit)
    {
        return;
    }


    if (!m_backgroundTexture.loadFromFile("../assets/Screens/EndScreen.jpg"))
    {
        sf::err() << "Could not load background image\n";
        return;
    }

    // Create and set the background sprite
    m_backgroundSprite.setTexture(m_backgroundTexture);
    m_backgroundSprite.setScale(1.7F, 1.5F);
    m_backgroundSprite.setPosition(m_game->getWindow().getView().getCenter());
    m_backgroundSprite.setOrigin(m_backgroundSprite.getLocalBounds().width * 0.5F,
                                 m_backgroundSprite.getLocalBounds().height * 0.5F);

    if (!m_font.loadFromFile("../assets/ARCADECLASSIC.TTF"))
    {
        sf::err() << "Could not load font\n";
        return;
    }
    m_text.setPosition(m_game->getWindow().getView().getCenter());
    m_text.setString("The Knights caught you!");
    m_text.setFillColor(sf::Color::Black);
    m_text.setFont(m_font);
    m_text.setOrigin(m_text.getLocalBounds().width * 0.5F, m_text.getLocalBounds().height * 0.5F);
    int offsetHeightTextStart = -250;
    m_text.move(0, offsetHeightTextStart);


    m_text2.setPosition(m_game->getWindow().getView().getCenter());
    m_text2.setString("Press R to Restart");
    m_text2.setFillColor(sf::Color::White);
    m_text2.setFont(m_font);
    m_text2.setOrigin(m_text.getLocalBounds().width * 0.5F - 50, m_text.getLocalBounds().height * 0.5F - 250);

    // position for the score text
    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(30);
    m_scoreText.setFillColor(sf::Color::Black);
    m_scoreText.setOrigin(m_scoreText.getLocalBounds().width * 0.5F, m_scoreText.getLocalBounds().height * 0.5F);
    sf::FloatRect textBounds   = m_text.getGlobalBounds();
    int           offsetHeight = 20;
    m_scoreText.setPosition(m_text.getPosition().x, m_text.getPosition().y + textBounds.height + offsetHeight); // adjust the position of the score text

    m_view = m_game->getWindow().getView();

    if (!m_music.openFromFile("../assets/Musik/Menu.ogg"))
    {
        std::cerr << "Failed to load music file" << std::endl;
    }
    else
    {
        m_music.setLoop(true);
        m_music.play();
    }

    m_isInit = true;
}

void EndState::loadScoreFromFile(const std::string& filename)
{
    std::ifstream file(filename);

    if (file.is_open())
    {
        file >> yourScore;
        file.close();

        // Update m_scoreText after loading the score
        m_scoreText.setString("Here is your Score " + std::to_string(yourScore));
    }
    else
    {
        sf::err() << "Error opening file: " << filename << std::endl;
    }
}


void EndState::loadHighscoresFromFile(const std::string& filename)
{
    std::ifstream file(filename);

    if (file.is_open())
    {
        int score;
        while (file >> score)
        {
            highscores.push_back(score);
        }

        file.close();
    }
}

void EndState::update(float delta)
{
    PROFILE_FUNCTION();

    if (InputManager::getInstance().isKeyPressed("Replay"))
    {
        m_gameStateManager->setState("MenuState");
        return;
    }

    m_game->getWindow().setView(m_view);
}

void EndState::draw()
{
    PROFILE_FUNCTION();

    m_game->getWindow().draw(m_backgroundSprite); 
    m_game->getWindow().draw(m_text);
    m_game->getWindow().draw(m_text2);             
    m_game->getWindow().draw(m_scoreText);        

    // score text configuration and position calculation for the highscore header text
    sf::Text highscoreHeaderText;
    highscoreHeaderText.setFont(m_font);
    highscoreHeaderText.setCharacterSize(30);
    highscoreHeaderText.setFillColor(sf::Color::White);
    highscoreHeaderText.setString("Highscore");
    highscoreHeaderText.setOrigin(highscoreHeaderText.getLocalBounds().width * 0.5F, 0.0F);
    int offsetHeight = 50;
    highscoreHeaderText.setPosition(m_scoreText.getPosition().x,
                                    m_scoreText.getPosition().y + m_scoreText.getGlobalBounds().height + offsetHeight);

    // Draw the highscore header text
    m_game->getWindow().draw(highscoreHeaderText);

    // highscore text configuration
    sf::Text highscoreText;
    highscoreText.setFont(m_font);
    highscoreText.setCharacterSize(30);
    highscoreText.setFillColor(sf::Color::White);

    // set the highscore string
    std::string highscoreString;
    for (size_t i = 0; i < highscores.size(); ++i)
    {
        highscoreString += std::to_string(i + 1) + "   " + std::to_string(highscores[i]) + "\n";
    }
    highscoreText.setString(highscoreString);

    // position the highscore text
    highscoreText.setOrigin(highscoreText.getLocalBounds().width * 0.5F, 0.0F);
    int offsetHeightHighscoreText = 10;
    highscoreText.setPosition(highscoreHeaderText.getPosition().x,
                              highscoreHeaderText.getPosition().y + highscoreHeaderText.getGlobalBounds().height + offsetHeightHighscoreText);

    // Draw the highscore text
    m_game->getWindow().draw(highscoreText);
}

void EndState::exit()
{
    PROFILE_FUNCTION();
    m_music.stop();

    m_game->getGui().removeAllWidgets();
    GameState::exit();
}
} // namespace mmt_gd
