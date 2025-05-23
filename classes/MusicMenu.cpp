#include "../headers/MusicMenu.h"
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#endif

MusicMenu::MusicMenu(sf::RenderWindow& window) : state(CLOSED) {
    if (!font.loadFromFile("Silkscreen/CyrilicOld.ttf")) {
        std::cerr << "Не удалось загрузить шрифт для меню музыки!" << std::endl;
    }

    menuButton.setSize(sf::Vector2f(40, 40));
    menuButton.setFillColor(sf::Color(180, 180, 220));
    menuButton.setOutlineThickness(2);
    menuButton.setOutlineColor(sf::Color::Black);

    menuText.setFont(font);
    menuText.setCharacterSize(24);
    menuText.setString("?");
    menuText.setFillColor(sf::Color::Black);

    menuPanel.setSize(sf::Vector2f(170, 120));
    menuPanel.setFillColor(sf::Color(230, 230, 255, 240));
    menuPanel.setOutlineThickness(2);
    menuPanel.setOutlineColor(sf::Color(100, 100, 180));

    musicOnText.setFont(font);
    musicOnText.setCharacterSize(18);
    musicOnText.setString("Музыка");
    musicOnText.setFillColor(sf::Color::Black);

    exitGameText.setFont(font);
    exitGameText.setCharacterSize(18);
    exitGameText.setString("Выход из игры");
    exitGameText.setFillColor(sf::Color::Black);

    updatePositions(window);
}

void MusicMenu::updatePositions(sf::RenderWindow& window) {
    menuButton.setPosition(window.getSize().x - 50, 10);
    menuText.setPosition(window.getSize().x - 42, 11);
    menuPanel.setPosition(window.getSize().x - 180, 60);
    musicOnText.setPosition(window.getSize().x - 170, 70);
    exitGameText.setPosition(window.getSize().x - 170, 110);

    musicOnBtnRect = sf::FloatRect(window.getSize().x - 170, 70, 160, 30);
    exitGameBtnRect = sf::FloatRect(window.getSize().x - 170, 110, 160, 30);
}

void MusicMenu::handleEvent(const sf::Event& event, sf::RenderWindow& window, sf::Music& music, bool& isMusicOn) {
    if (event.type == sf::Event::Resized) {
        updatePositions(window);
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePosF = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (menuButton.getGlobalBounds().contains(mousePosF)) {
            state = (state == CLOSED) ? OPEN : CLOSED;
        }
        if (state == OPEN) {
            if (musicOnBtnRect.contains(mousePosF)) {
                if (isMusicOn) {
                    music.pause();
                    isMusicOn = false;
                }
                else {
                    music.play();
                    isMusicOn = true;
                }
            }
            if (exitGameBtnRect.contains(mousePosF)) {
                window.close();
            }
        }
    }
}

void MusicMenu::draw(sf::RenderWindow& window, bool isMusicOn) {
    window.draw(menuButton);
    window.draw(menuText);

    if (state == OPEN) {
        window.draw(menuPanel);
        window.draw(musicOnText);
        window.draw(exitGameText);

        if (!isMusicOn) {
            sf::Text offText("Отключено", font, 14);
            offText.setFillColor(sf::Color::Red);
            offText.setPosition(window.getSize().x - 90, 73);
            window.draw(offText);
        }
    }
}