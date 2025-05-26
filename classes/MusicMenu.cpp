#include "../headers/MusicMenu.h"
#include "../headers/Inventory.h"
#include "../headers/ConfirmationDialog.h"
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#endif

MusicMenu::MusicMenu(sf::RenderWindow& window) : state(CLOSED), pendingAction(NONE) {
    if (!font.loadFromFile("Silkscreen/CyrilicOld.ttf")) {
        std::cerr << "Не удалось загрузить шрифт для меню музыки!" << std::endl;
    }

    menuButton.setSize(sf::Vector2f(40, 40));
    menuButton.setFillColor(sf::Color(155, 212, 195, 240));
    menuButton.setOutlineThickness(2);
    menuButton.setOutlineColor(sf::Color(100, 100, 180));

    menuPanel.setSize(sf::Vector2f(170, 120));
    menuPanel.setFillColor(sf::Color(155, 212, 195, 240));
    menuPanel.setOutlineThickness(2);
    menuPanel.setOutlineColor(sf::Color(100, 100, 180));

    menuText.setFont(font);
    menuText.setCharacterSize(18);
    menuText.setString("");
    menuText.setFillColor(sf::Color(100, 100, 180));

    musicOnText.setFont(font);
    musicOnText.setCharacterSize(18);
    musicOnText.setString("Музыка");
    musicOnText.setFillColor(sf::Color(100, 100, 180));

    mainMenuText.setFont(font);
    mainMenuText.setCharacterSize(18);
    mainMenuText.setString("Главное меню");
    mainMenuText.setFillColor(sf::Color(100, 100, 180));

    exitGameText.setFont(font);
    exitGameText.setCharacterSize(18);
    exitGameText.setString("Выход из игры");
    exitGameText.setFillColor(sf::Color(100, 100, 180));

    if (!iconTexture.loadFromFile("sprites/music_icon.png")) {
        std::cerr << "Не удалось загрузить иконку для меню музыки!" << std::endl;
    }
    iconSprite.setTexture(iconTexture);

    float iconSize = 40.0f;
    iconSprite.setScale(
        iconSize / iconTexture.getSize().x,
        iconSize / iconTexture.getSize().y
    );

    updatePositions(window);
}

void MusicMenu::close() {
    state = CLOSED;
}

void MusicMenu::updatePositions(sf::RenderWindow& window) {
    menuButton.setPosition(window.getSize().x - 50, 10);
    menuText.setPosition(window.getSize().x - 42, 11);
    menuPanel.setPosition(window.getSize().x - 180, 60);
    iconSprite.setPosition(window.getSize().x - 55 + 8, 5 + 8);

    float startY = 70;
    float step = 35;

    musicOnText.setPosition(window.getSize().x - 170, startY);
    mainMenuText.setPosition(window.getSize().x - 170, startY + step);
    exitGameText.setPosition(window.getSize().x - 170, startY + 2 * step);

    musicOnBtnRect = sf::FloatRect(window.getSize().x - 170, startY, 160, 25);
    mainMenuBtnRect = sf::FloatRect(window.getSize().x - 170, startY + step, 160, 25);
    exitGameBtnRect = sf::FloatRect(window.getSize().x - 170, startY + 2 * step, 160, 25);
}

void MusicMenu::handleEvent(const sf::Event& event, sf::RenderWindow& window, sf::Music& music, bool& isMusicOn, Inventory& inventory) {
    if (event.type == sf::Event::Resized) {
        updatePositions(window);
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePosF = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (menuButton.getGlobalBounds().contains(mousePosF)) {
            state = (state == CLOSED) ? OPEN : CLOSED;
        }
        else if (state == OPEN) {
            sf::Font font;
            if (!font.loadFromFile("Silkscreen/CyrilicOld.ttf")) {
                std::cerr << "Ошибка загрузки шрифта!" << std::endl;
                return;
            }

            if (musicOnBtnRect.contains(mousePosF)) {
                isMusicOn = !isMusicOn;
                isMusicOn ? music.play() : music.pause();
            }
            else if (mainMenuBtnRect.contains(mousePosF)) {
                ConfirmationDialog confirmDialog(window, font, "Вы хотите перезаписать сохранение перед выходом в главное меню?");
                bool confirmed = confirmDialog.show();

                if (confirmed && inventory.saveDataToFile("InventoryData.txt")) {
                    std::cout << "Данные инвентаря успешно сохранены." << std::endl;
                } else {
                    std::cerr << "Ошибка сохранения данных инвентаря!" << std::endl;
                }

                pendingAction = MAIN_MENU;
            }
            else if (exitGameBtnRect.contains(mousePosF)) {
                ConfirmationDialog confirmExitDialog(window, font, "Вы хотите перезаписать сохранение перед выходом из игры?");
                bool confirmedExit = confirmExitDialog.show();

                if (confirmedExit && inventory.saveDataToFile("InventoryData.txt")) {
                    std::cout << "Данные инвентаря успешно сохранены." << std::endl;
                } else {
                    std::cerr << "Ошибка сохранения данных инвентаря!" << std::endl;
                }

                pendingAction = EXIT_GAME;
                window.close();
            }
            else {
                close();
            }
        }
    }
}


void MusicMenu::draw(sf::RenderWindow& window, bool isMusicOn) {
    window.draw(menuButton);
    window.draw(iconSprite);
    window.draw(menuText);

    if (state == OPEN) {
        window.draw(menuPanel);
        window.draw(musicOnText);
        window.draw(mainMenuText);
        window.draw(exitGameText);

        if (!isMusicOn) {
            sf::Text offText("Отключено", font, 14);
            offText.setFillColor(sf::Color(100, 100, 180));
            offText.setPosition(window.getSize().x - 90, 73);
            window.draw(offText);
        }
    }
}

MusicMenu::Action MusicMenu::pollAction() {
    Action ret = pendingAction;
    pendingAction = NONE;
    return ret;
}
