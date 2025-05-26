#include "../headers/ConfirmationDialog.h"
#include <sstream>

ConfirmationDialog::ConfirmationDialog(sf::RenderWindow& window, const sf::Font& font, const std::string& message)
    : window(window) {

    dialogBox.setSize(sf::Vector2f(500, 180));
    dialogBox.setFillColor(sf::Color(180, 200, 220, 240)); // Светло-голубой фон
    dialogBox.setOutlineColor(sf::Color(100, 100, 180));
    dialogBox.setOutlineThickness(3);
    dialogBox.setPosition(window.getSize().x / 2 - dialogBox.getSize().x / 2,
        window.getSize().y / 2 - dialogBox.getSize().y / 2);

    messageText.setFont(font);
    messageText.setCharacterSize(22);
    messageText.setFillColor(sf::Color(50, 50, 80));
    formatText(message, 460);
    centerText(messageText, dialogBox.getPosition().x + dialogBox.getSize().x / 2,
        dialogBox.getPosition().y + 20);


    yesButton.setFont(font);
    yesButton.setString("Да");
    yesButton.setCharacterSize(26);
    yesButton.setFillColor(sf::Color(50, 50, 80));
    centerText(yesButton, dialogBox.getPosition().x + dialogBox.getSize().x / 4,
        dialogBox.getPosition().y + dialogBox.getSize().y - 50);

    noButton.setFont(font);
    noButton.setString("Нет");
    noButton.setCharacterSize(26);
    noButton.setFillColor(sf::Color(50, 50, 80));
    centerText(noButton, dialogBox.getPosition().x + 3 * dialogBox.getSize().x / 4,
        dialogBox.getPosition().y + dialogBox.getSize().y - 50);
}

void ConfirmationDialog::centerText(sf::Text& text, float x, float y) {
    text.setPosition(x - text.getLocalBounds().width / 2, y);
}

void ConfirmationDialog::formatText(const std::string& message, float maxWidth) {
    std::stringstream formattedText;
    float currentWidth = 0;
    std::string word;
    sf::Text tempText(messageText);

    std::istringstream words(message);
    while (words >> word) {
        tempText.setString(word);
        float wordWidth = tempText.getLocalBounds().width;

        if (currentWidth + wordWidth > maxWidth) {
            formattedText << "\n";
            currentWidth = 0;
        }

        formattedText << word << " ";
        currentWidth += wordWidth;
    }

    messageText.setString(formattedText.str());
}

bool ConfirmationDialog::show() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return false;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

                if (yesButton.getGlobalBounds().contains(worldPos)) {
                    return true;
                }
                else if (noButton.getGlobalBounds().contains(worldPos)) {
                    return false;
                }
            }
        }

        window.clear();
        window.draw(dialogBox);
        window.draw(messageText);
        window.draw(yesButton);
        window.draw(noButton);
        window.display();
    }
    return false;
}