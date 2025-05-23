#include"../headers/MessagePanel.h"

MessagePanel::MessagePanel() {
    font.loadFromFile("Silkscreen/CyrilicOld.ttf");
    panelSize = sf::Vector2f(470, 150); 
    position = sf::Vector2f(300, 640);

    background.setFillColor(sf::Color(20, 20, 20, 180));
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(2);
    background.setSize(panelSize);
    background.setPosition(position);
}

void MessagePanel::addMessage(const std::string& msg, float timeout) {
    if (messages.size() >= maxMessages)
        messages.pop_front();
    MessageInfo info{ msg, sf::Clock() };
    messages.push_back(info);
}

void MessagePanel::update() {
    while (!messages.empty() && messages.front().timer.getElapsedTime().asSeconds() > messageTimeout)
        messages.pop_front();
}

void MessagePanel::draw(sf::RenderWindow& window) {
    update();
    if (messages.empty()) return;

    background.setPosition(position);
    background.setSize(panelSize);
    window.draw(background);

    float lineHeight = 28; // ещё компактнее
    float y = position.y + 10;
    int shown = 0;
    for (auto it = messages.rbegin(); it != messages.rend(); ++it) {
        sf::Text text(it->text, font, 18); // ещё меньше шрифт
        text.setPosition(position.x + 10, y);
        text.setFillColor(sf::Color::White);
        window.draw(text);
        y += lineHeight;
        shown++;
        if (shown >= 5) break; // максимум 2 сообщения на маленькой панели
    }
}