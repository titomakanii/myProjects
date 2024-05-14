#pragma once

#include "SFML/Window.hpp"

#include <unordered_map>

namespace mmt_gd
{
class InputManager
{
public:
    static InputManager& getInstance();
    InputManager(const InputManager& rhv)             = delete;
    InputManager(InputManager&& rhv)                  = delete;
    InputManager&  operator=(const InputManager& rhv) = delete;
    InputManager&& operator=(InputManager&& rhv)      = delete;

    void process(const sf::Event& event);

    void update();

    void bind(const std::string& action, int keyCode, int playerIdx = 0);

    void unbind(const std::string& action, int playerIdx = 0);

    bool isKeyDown(const int keyCode) const
    {
        ffAssertMsg(keyCode >= 0 && keyCode < sf::Keyboard::KeyCount,
                    "KeyCode out of bounds") return m_currentFrame.m_keys[keyCode];
    }

    bool isKeyUp(const int keyCode) const
    {
        ffAssertMsg(keyCode >= 0 && keyCode < sf::Keyboard::KeyCount,
                    "KeyCode out of bounds") return !m_currentFrame.m_keys[keyCode];
    }

    bool isKeyPressed(const int keyCode) const
    {
        ffAssertMsg(keyCode >= 0 && keyCode < sf::Keyboard::KeyCount,
                    "KeyCode out of bounds") return m_currentFrame.m_keys[keyCode] &&
            !m_lastFrame.m_keys[keyCode];
    }

    bool isKeyReleased(const int key_code) const
    {
        ffAssertMsg(key_code >= 0 && key_code < sf::Keyboard::KeyCount,
                    "KeyCode out of bounds") return !m_currentFrame.m_keys[key_code] &&
            m_lastFrame.m_keys[key_code];
    }

    bool isKeyDown(const std::string& action, int playerIdx = 0);

    bool isKeyUp(const std::string& action, int playerIdx = 0);

    bool isKeyPressed(const std::string& action, int playerIdx = 0);

    bool isKeyReleased(const std::string& action, int playerIdx = 0);

    sf::Vector2f getMousePosition() const;

    void setRenderWindow(sf::RenderWindow* window)
    {
        m_renderWindow = window;
    }

private:
    InputManager()  = default;
    ~InputManager() = default;


    int getKeyForAction(const std::string& action, int playerIdx);

    struct FrameData
    {
        bool m_keys[sf::Keyboard::KeyCount];
    };

    FrameData m_lastFrame{};
    FrameData m_currentFrame{};
    FrameData m_eventFrame{};

    sf::RenderWindow* m_renderWindow{nullptr};

    static constexpr int                 PlayerCount = 1; ///< maximum allowed players. Can be increased if needed.
    std::unordered_map<std::string, int> m_actionBinding[PlayerCount];
};
} // namespace mmt_gd
