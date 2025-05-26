#ifndef CONFIRMATIONDIALOG_H
#define CONFIRMATIONDIALOG_H

#include <SFML/Graphics.hpp>
#include <string>

class ConfirmationDialog {
public:
    ConfirmationDialog(sf::RenderWindow& window, const sf::Font& font, const std::string& message);

    bool show();

private:
    sf::RenderWindow& window;
    sf::RectangleShape dialogBox;
    sf::Text messageText; 
    sf::Text yesButton;
    sf::Text noButton;

    void centerText(sf::Text& text, float x, float y);
    void formatText(const std::string& message, float maxWidth); // Добавляем объявление метода
};

#endif
