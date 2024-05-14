// MMP2 Project made by: Nicolas van Renen, Andrè Linder
// Music is copyrightfree and no author is required
#include "stdafx.h"
#include "MainState.hpp"

#include "CameraRenderComponent.hpp"
#include "ColliderComponent.hpp"
#include "Game.hpp"
#include "InputManager.hpp"
#include "TileMapLoader.hpp"
#include "Tileson.hpp"
#include "TransformAnimationComponent.hpp"
#include "TransformAnimationSmoothFollow.hpp"
#include "PlayerHealthComponent.hpp"
#include "AIMovementComponent.hpp"
#include "PowerUpManager.hpp"
#include "PlayerMoveComponent.hpp"
#include "PointsComponent.hpp"

#include <memory>
#include <thread>
#include <random>

namespace mmt_gd
{
MainState::MainState(GameStateManager* gameStateManager, Game* game) :
GameState(gameStateManager, game),
m_spriteManager(game->getWindow()),
m_elapsedTime(0.0f),
yourScore(0),
m_powerUpTimer(0.0f)
{
}
float       timeSinceLastPoint = 0.0f;
const float pointsInterval     = 1.0f;


void MainState::init()
{
    PROFILE_FUNCTION();

    highscores.clear();

    m_gameObjectManager.init();
    m_spriteManager.init();
    m_physicsManager.init();


    // load tile map/level
    {
        PROFILE_SCOPE("Load Tile Map");
        const auto resourcePath = fs::path{"../"} / "assets";
        const auto mapPath      = resourcePath / "map2.0.tmj";

        tson::Tileson t;
        if (const std::unique_ptr<tson::Map> map = t.parse(mapPath); map->getStatus() == tson::ParseStatus::OK)
        {
            TileMapLoader::loadTileLayers(map, resourcePath, m_spriteManager);
            TileMapLoader::loadObjectLayers(map, resourcePath, m_spriteManager);


            //std::cout << map->getSize().x << std::endl;
            auto powerUpManager = &PowerUpManager::getInstance();
            auto borderOffset   = 50;
            powerUpManager->setPowerUpSpawnArea(std::pair<std::pair<int, int>, std::pair<int, int>>(
                {{borderOffset, borderOffset},
                 {map->getSize().x * map->getTileSize().x - borderOffset,
                  map->getSize().y * map->getTileSize().y - borderOffset}}));
            powerUpManager->init();
        }
        else
        {
            std::cerr << "Error loading " << mapPath << std::endl;
        }
    }

    const auto player = m_gameObjectManager.getGameObject("Player0");
    // Moving camera
    {
        const auto camera = GameObject::create("Camera");

        const auto renderComp = camera->addComponent<CameraRenderComponent>(*camera,
                                                                            m_game->getWindow(),
                                                                            m_game->getWindow().getView());

        camera->addComponent<TransformAnimationComponent>(*camera,
                                                          std::make_shared<mmt::TransformAnimationSmoothFollow>(player, 10.F));


        if (!camera->init())
            ffErrorMsg("Could not initialize camera");

        m_gameObjectManager.addGameObject(camera);
        m_spriteManager.setCamera(renderComp.get());
    }

    // Define layer order manually here. Could come from custom file settings.
    m_spriteManager.setLayerOrder({"Floor", "Background", "Objects", "GameObjects", "Top"});
    if (!m_music.openFromFile("../assets/Musik/Main.ogg"))
    {
        std::cerr << "Failed to load music file" << std::endl;
    }
    else
    {
        m_music.setLoop(true);
        m_music.play();
    }
}

void MainState::updatePowerUpPositions()
{
    auto& powerUpManager = PowerUpManager::getInstance();

    // Iterate over all active power-ups and update their positions
    for (auto& gameObject : powerUpManager.m_activePowerUps)
    {
        // Generate random coordinates based on the power-up spawn area
        std::random_device              rd;
        std::mt19937                    gen(rd());
        std::uniform_int_distribution<> disX(powerUpManager.m_powerUpSpawnArea.first.first,
                                             powerUpManager.m_powerUpSpawnArea.second.first);
        std::uniform_int_distribution<> disY(powerUpManager.m_powerUpSpawnArea.first.second,
                                             powerUpManager.m_powerUpSpawnArea.second.second);

        gameObject->setPosition(sf::Vector2f(disX(gen), disY(gen)));

        // Move the corresponding physics object, if necessary
        auto rigidBody = gameObject->getComponent<RigidBodyComponent>();
        PhysicsManager::moveB2Body(*rigidBody->getB2Body(), gameObject->getPosition(), 0);
    }
}


void MainState::update(const float deltaTime)
{
    PROFILE_FUNCTION();
    if (InputManager::getInstance().isKeyPressed("Exit"))
    {
        m_gameStateManager->setState("EndState");
        return;
    }

    m_powerUpTimer += deltaTime;

    // Update power-up positions every 15 seconds
    if (m_powerUpTimer >= 15.0f)
    {
        m_powerUpTimer = 0.0f;

        updatePowerUpPositions();
    }

    EventBus::getInstance().processEvents(deltaTime);
    m_gameObjectManager.update(deltaTime);
    m_physicsManager.update(deltaTime);
    GameObject::Ptr playerGameObject = m_gameObjectManager.getGameObject("Player0");
    if (playerGameObject)
    {
        for (int i = 1; i <= 10; ++i)
        {
            std::string enemyId         = "Enemy" + std::to_string(i);
            auto        enemyGameObject = m_gameObjectManager.getGameObject(enemyId);
            if (enemyGameObject)
            {
                auto enemyMovementComponent = enemyGameObject->getComponent<AIMovementComponent>();
                if (enemyMovementComponent)
                {
                    enemyMovementComponent->setTargetPosition(playerGameObject->getPosition());
                }
            }
        }
    }
    timeSinceLastPoint += deltaTime;

    // Add points if the time interval has passed and player position has changed
    if (timeSinceLastPoint >= pointsInterval)
    {
        if (auto playerGameObject = m_gameObjectManager.getGameObject("Player0"))
        {
            auto pointsComponent = playerGameObject->getComponent<PointsComponent>();
            if (pointsComponent)
            {
                if ((std::abs(playerGameObject->getPosition().x - lastPlayerPosition.x) >= 30.0f && std::abs(playerGameObject->getPosition().y - lastPlayerPosition.y) >= 20.0f) ||
                    (std::abs(playerGameObject->getPosition().x - lastPlayerPosition.x) >= 20.0f &&
                     std::abs(playerGameObject->getPosition().y - lastPlayerPosition.y) >= 30.0f))
                {
                    pointsComponent->addPoints(1);
                    lastPlayerPosition = playerGameObject->getPosition();
                }
                timeSinceLastPoint = 0.0f;
            }
        }
    }

    if (auto playerGameObject = m_gameObjectManager.getGameObject("Player0"))
    {
        auto playerHealthComponent = playerGameObject->getComponent<HealthComponent>();
        if (playerHealthComponent)
        {
            playerHealthComponent->update(deltaTime);
            if (playerHealthComponent->getHealth() <= 0)
            {
                m_gameStateManager->setState("EndState");
            }
        }
    }

    m_elapsedTime += deltaTime;
}


void MainState::draw()
{
    PROFILE_FUNCTION();
    m_spriteManager.draw();
    if (!m_font.loadFromFile("../assets/ARCADECLASSIC.TTF"))
    {
        sf::err() << "Could not load font\n";
        return;
    }
    sf::RenderWindow& window   = m_game->getWindow();
    sf::View          view     = window.getView();
    sf::Vector2f      viewSize = view.getSize();

    sf::Text healthText;
    healthText.setFont(m_font);             
    healthText.setCharacterSize(30);          
    healthText.setFillColor(sf::Color::Red);


    GameObject::Ptr playerGameObject = m_gameObjectManager.getGameObject("Player0");
    if (playerGameObject)
    {
        auto playerHealthComponent = playerGameObject->getComponent<HealthComponent>();
        if (playerHealthComponent)
        {
            // Calculate the health percentage
            float healthPercentage = static_cast<float>(playerHealthComponent->getHealth()) / 200;

            // Calculate the size of the health bar
            float healthBarWidth  = viewSize.x - 10.0f;
            float healthBarHeight = 20.0f;

           // Calculate the position of the health bar (bottom left)
            float healthBarX = view.getCenter().x - viewSize.x / 2.0f + 5.0f;
            float healthBarY = view.getCenter().y + viewSize.y / 2.0f - healthBarHeight - 5.0f;

            // Create a rectangle shape for the health bar
            sf::RectangleShape healthBar(sf::Vector2f(healthBarWidth * healthPercentage, healthBarHeight));
            healthBar.setPosition(healthBarX, healthBarY);
            healthBar.setFillColor(sf::Color::Green);

            sf::Text healthLabel;
            healthLabel.setFont(m_font);
            healthLabel.setCharacterSize(16);
            healthLabel.setFillColor(sf::Color::White);
            healthLabel.setString("Health");
            healthLabel.setPosition(healthBarX, healthBarY - 20.0f);

            window.draw(healthBar);
            window.draw(healthLabel);
        }
    }

    healthText.setPosition(view.getCenter().x - viewSize.x / 2.f + 5, view.getCenter().y - viewSize.y / 2.f);

    window.draw(healthText);
    drawPoints();
    drawDashCooldownCircle();
}

void MainState::drawDashCooldownCircle()
{
    GameObject::Ptr playerGameObject    = m_gameObjectManager.getGameObject("Player0");
    auto            playerMoveComponent = playerGameObject->getComponent<PlayerMoveComponent>();

    sf::RenderWindow& window   = m_game->getWindow();
    sf::View          view     = window.getView();
    sf::Vector2f      viewSize = view.getSize();

    const float circleRadius           = 50.0f;
    const float circleOutlineThickness = 5.0f;
    const float arcThickness           = 15.0f;
    const float cooldownPercentage     = std::max(0.0f,
                                              std::min(1.0f,
                                                       playerMoveComponent->getCooldownTimer() /
                                                           playerMoveComponent->getDashCooldown()));

    // Calculate the angle of the arc based on the cooldown percentage
    const float startAngle = -90.0f;
    const float endAngle   = startAngle + 360.0f * cooldownPercentage;

    // Calculate the number of points to draw
    const int   numPoints = 50;
    const float angleStep = (endAngle - startAngle) / (numPoints - 1);

    // Calculate points for the arcs
    for (float thickness = 0; thickness < arcThickness; ++thickness)
    {
        // Create a vertex array to store the points of the arc
        sf::VertexArray arc(sf::LineStrip, numPoints);

        for (int i = 0; i < numPoints; ++i)
        {
            float angle   = startAngle + angleStep * i;
            float radians = angle * 3.14159265359f / 180.0f;
            float innerRadius = circleRadius - circleOutlineThickness - thickness * 0.5f;
            float x         = circleRadius + std::cos(radians) * innerRadius;
            float y         = circleRadius + std::sin(radians) * innerRadius;
            arc[i].position = sf::Vector2f(x, y);
            arc[i].color    = sf::Color::Blue;
        }

        float arcX = view.getCenter().x + viewSize.x / 2.0f - circleRadius * 2;
        float arcY = view.getCenter().y + viewSize.y / 2.0f - circleRadius * 2;

        for (int i = 0; i < numPoints; ++i)
        {
            arc[i].position += sf::Vector2f(arcX, arcY);
        }

        window.draw(arc);
    }
}

void MainState::drawPoints()
{
    sf::RenderWindow& window   = m_game->getWindow();
    sf::View          view     = window.getView();
    sf::Vector2f      viewSize = view.getSize();

    sf::Text timerText;
    timerText.setFont(m_font);
    timerText.setCharacterSize(30);
    timerText.setFillColor(sf::Color::White);

    timerText.setPosition(view.getCenter().x - 30, view.getCenter().y - viewSize.y / 2.f + 5);
    yourScore = static_cast<int>(m_elapsedTime);


    if (auto playerGameObject = m_gameObjectManager.getGameObject("Player0"))
    {
        auto pointsComponent = playerGameObject->getComponent<PointsComponent>();
        if (pointsComponent)
        {
            yourScore                = pointsComponent->getPoints();
            std::stringstream ss;
            ss << "" << std::setw(4) << std::setfill('0') << yourScore;
            timerText.setString(ss.str());
        }
    }

    window.draw(timerText);
}


void MainState::savePointsToHighscoreFile(const std::string& filename, int points)
{
    loadHighscoresFromFile(filename);

    addScoreToHighscores(points);

    std::sort(highscores.rbegin(), highscores.rend());

    if (highscores.size() > 8)
    {
        highscores.resize(8);
    }

    std::ofstream file(filename);

    if (file.is_open())
    {
        for (int score : highscores)
        {
            file << score << std::endl;
        }

        file.close();
    }
    else
    {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
}

void MainState::loadHighscoresFromFile(const std::string& filename)
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

void MainState::addScoreToHighscores(int score)
{
    highscores.push_back(score);
}

int MainState::getYourScore() const
{
    return static_cast<int>(m_elapsedTime);
}


void MainState::addPoints(int points)
{
    if (auto playerGameObject = m_gameObjectManager.getGameObject("Player0"))
    {
        auto pointsComponent = playerGameObject->getComponent<PointsComponent>();
        if (pointsComponent)
        {
            pointsComponent->addPoints(points);
        }
    }
}
void MainState::saveCurrentScoreToFile(const std::string& filename) const
{
    std::ofstream file(filename);

    if (file.is_open())
    {
        //std::cout << "Saving score to file: " << filename << std::endl;
        //std::cout << "Score: " << yourScore << std::endl;
        file << yourScore << std::endl;
        file.close();
    }
    else
    {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
}
void MainState::exit()
{
    PROFILE_FUNCTION();
    PowerUpManager::getInstance().shutdown();
    m_gameObjectManager.shutdown();
    m_spriteManager.shutdown();
    m_physicsManager.shutdown();
    
    
    
    m_music.stop();
    if (auto playerGameObject = m_gameObjectManager.getGameObject("Player0"))
    {
        auto pointsComponent = playerGameObject->getComponent<PointsComponent>();
        if (pointsComponent)
        {
            yourScore = pointsComponent->getPoints();
        }
    }
    savePointsToHighscoreFile("highscores.txt", yourScore);
    saveCurrentScoreToFile("score.txt");

    //displayHighscores();
    m_elapsedTime = 0;


}

} // namespace mmt_gd