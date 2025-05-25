#include "../headers/Button.h"

Button::Button(const std::string& imagePath, float x, float y, float width, float height, std::function<void()> onClick)
    : onClick(onClick)
{
    shape.setPosition(x, y);
    shape.setSize({ width, height });
    shape.setFillColor(sf::Color(80, 80, 80, 0)); 
    shape.setOutlineThickness(0);

    texture.loadFromFile(imagePath);
    sprite.setTexture(texture);
    float scaleX = width / texture.getSize().x;
    float scaleY = height / texture.getSize().y;
    sprite.setScale(scaleX, scaleY);
    sprite.setPosition(x, y);
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(sprite);
}

bool Button::isMouseOver(const sf::Vector2f& mousePos) {
    return shape.getGlobalBounds().contains(mousePos);
}

bool Button::handleEvent(const sf::Event& event, const sf::Vector2f& mousePos) {
    hovered = isMouseOver(mousePos);
    if (event.type == sf::Event::MouseButtonPressed && hovered) {
        if (onClick) onClick();
        return true;
    }
    return false;
}