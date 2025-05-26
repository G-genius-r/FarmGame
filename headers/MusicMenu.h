#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Farm.h"
#include "NotificationPanel.h"

class MusicMenu {
public:
    enum State { CLOSED, OPEN };
    enum Action { NONE, EXIT_GAME, MAIN_MENU };

    MusicMenu(sf::RenderWindow& window);
    void updatePositions(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window, sf::Music& music, bool& isMusicOn, Farm& farm);
    void draw(sf::RenderWindow& window, bool isMusicOn);
    void close();
    bool isOpen() const { return state == OPEN; }
    Action pollAction();

private:
    State state;
    Action pendingAction;

    sf::Text saveGameText;
    sf::FloatRect saveGameBtnRect;

    sf::Texture iconTexture;
    sf::Sprite iconSprite;

    sf::Font font;
    sf::RectangleShape menuButton;
    sf::Text menuText;

    sf::RectangleShape menuPanel;
    sf::Text musicOnText;
    sf::Text mainMenuText;
    sf::Text exitGameText;

    sf::FloatRect musicOnBtnRect;
    sf::FloatRect mainMenuBtnRect;
    sf::FloatRect exitGameBtnRect;
};