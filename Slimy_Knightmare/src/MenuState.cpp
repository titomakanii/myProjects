// MMP2 Project made by: Nicolas van Renen, Andrè Linder
// Music is copyrightfree and no author is required
#include "stdafx.h"

#include "MenuState.hpp"

#include "Game.hpp"
#include "GameStateManager.hpp"
#include "InputManager.hpp"
#include "TGUI/TGUI.hpp"


namespace mmt_gd
{
using namespace std;

void MenuState::init()
{
    PROFILE_FUNCTION();

    if (m_isInit)
    {
        return;
    }

    if (!m_backgroundTexture.loadFromFile("../assets/Screens/Test.jpg"))
    {
        sf::err() << "Could not load background image\n";
        return;
    }

    // Create and set the background sprite
    m_backgroundSprite.setTexture(m_backgroundTexture);
    m_backgroundSprite.setPosition(m_game->getWindow().getView().getCenter()); // Position the sprite in the middle of the screen
    m_backgroundSprite.setOrigin(m_backgroundSprite.getLocalBounds().width * 0.5F,
                                 m_backgroundSprite.getLocalBounds().height * 0.5F);

    if (!m_font.loadFromFile("../assets/ARCADECLASSIC.TTF"))
    {
        sf::err() << "Could not load font\n";
        return;
    }
    m_text.setPosition(m_game->getWindow().getView().getCenter());
    m_text.setString("Press space to start");
    m_text.setFillColor(sf::Color::White);
    m_text.setFont(m_font);
    m_text.setOrigin(m_text.getLocalBounds().width * 0.5F, m_text.getLocalBounds().height * 0.5F - 250);

    m_view = m_game->getWindow().getView();

    m_isInit = true;


    if (!m_music.openFromFile("../assets/Musik/Menu.ogg"))
    {
        //std::cerr << "Failed to load music file" << std::endl;
    }
    else
    {
        m_music.setLoop(true);
        m_music.play(); //start and loop the music
    }
}

void MenuState::update(float delta)
{
    PROFILE_FUNCTION();

    m_game->getWindow().setView(m_view);

     if (const auto btn = dynamic_pointer_cast<tgui::Button>(m_game->getGui().get("StartGameBtn")))
    {
        // Calculate the position to place the button in the middle bottom
        float buttonWidth  = btn->getSize().x;
        float buttonHeight = btn->getSize().y;

        float windowWidth  = static_cast<float>(m_game->getWindow().getSize().x);
        float windowHeight = static_cast<float>(m_game->getWindow().getSize().y);

        float xPosition = (windowWidth - buttonWidth) / 2.0f;
        float yPosition = windowHeight - buttonHeight - 100.0f; // You can adjust the offset as needed

        btn->setPosition(xPosition, yPosition);
        btn->onClick([&manager = m_gameStateManager] { manager->setState("MainState"); });
    }

    if (InputManager::getInstance().isKeyPressed("Select"))
    {
        m_gameStateManager->setState("MainState");
    }
}

void MenuState::draw()
{
    PROFILE_FUNCTION();

    m_game->getWindow().draw(m_backgroundSprite);
    m_game->getWindow().draw(m_text);
}

void MenuState::exit()
{
    PROFILE_FUNCTION();
    m_music.stop();

    m_game->getGui().removeAllWidgets();
    GameState::exit();
}
} // namespace mmt_gd
