#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

class Button {
public:
    Button(const std::string& imagePath, float x, float y, float width, float height, std::function<void()> onClick);

    void draw(sf::RenderWindow& window);
    bool isMouseOver(const sf::Vector2f& mousePos);
    bool handleEvent(const sf::Event& event, const sf::Vector2f& mousePos); 

private:
    sf::RectangleShape shape;
    sf::Sprite sprite;
    sf::Texture texture;
    bool hovered = false;
    std::function<void()> onClick;
};