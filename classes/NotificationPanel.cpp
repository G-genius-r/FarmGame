#include "../headers/NotificationPanel.h"

NotificationPanel::NotificationPanel() {
    font.loadFromFile("Silkscreen/CyrilicOld.ttf");
    panelWidth = 380.f;
    panelHeight = 40.f;
    charSize = 20;
}

void NotificationPanel::addMessage(const std::string& msg, float duration) {
    notifications.push_back({ msg, sf::Clock(), duration });
    if (notifications.size() > 5)
        notifications.pop_front();
}

void NotificationPanel::update() {
    while (!notifications.empty() && notifications.front().timer.getElapsedTime().asSeconds() > notifications.front().duration) {
        notifications.pop_front();
    }
}

void NotificationPanel::draw(sf::RenderWindow& window) {
    update();
    float margin = 8.f;
    sf::Vector2u winSize = window.getSize();
    // Начинаем от нижнего края и поднимаемся вверх
    for (size_t i = 0; i < notifications.size(); ++i) {
        float bg_x = winSize.x - panelWidth - 20;
        // Сообщения "растут" вверх от нижнего края:
        float bg_y = winSize.y - panelHeight - 20 - i * (panelHeight + margin);

        sf::RectangleShape bg(sf::Vector2f(panelWidth, panelHeight));
        bg.setFillColor(sf::Color(30, 30, 30, 180));
        bg.setOutlineColor(sf::Color(200, 170, 60, 180));
        bg.setOutlineThickness(2.f);
        bg.setPosition(bg_x, bg_y);

        sf::Text text(notifications[notifications.size() - 1 - i].text, font, charSize);
        text.setFillColor(sf::Color::White);
        text.setPosition(bg.getPosition().x + 10, bg.getPosition().y + 7);

        window.draw(bg);
        window.draw(text);
    }
}