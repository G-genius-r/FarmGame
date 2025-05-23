#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include <string>

struct MessageInfo {
    std::string text;
    sf::Clock timer;
};

class MessagePanel {
public:
    MessagePanel();

    void addMessage(const std::string& msg, float timeout = 3.0f);
    void draw(sf::RenderWindow& window);
    void update();

    void setPosition(float x, float y) { position = sf::Vector2f(x, y); }
    void setSize(float width, float height) { panelSize = sf::Vector2f(width, height); }

private:
    std::deque<MessageInfo> messages;
    float messageTimeout = 3.0f;
    size_t maxMessages = 5;

    sf::Font font;
    sf::RectangleShape background;
    sf::Vector2f position;
    sf::Vector2f panelSize;
};