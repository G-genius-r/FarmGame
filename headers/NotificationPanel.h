#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include <string>

class NotificationPanel {
public:
    NotificationPanel();

    void addMessage(const std::string& msg, float duration = 3.0f);
    void update();
    void draw(sf::RenderWindow& window);

private:
    struct Notification {
        std::string text;
        sf::Clock timer;
        float duration;
    };
    std::deque<Notification> notifications;
    sf::Font font;
    float panelWidth;
    float panelHeight;
    unsigned int charSize;
};