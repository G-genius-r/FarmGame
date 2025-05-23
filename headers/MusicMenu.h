#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

enum MusicMenuState {
    MUSIC_MENU_CLOSED,
    MUSIC_MENU_OPEN
};

class MusicMenu {
public:
    enum State {
        CLOSED,
        OPEN
    };

    MusicMenu(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window, sf::Music& music, bool& isMusicOn);
    void draw(sf::RenderWindow& window, bool isMusicOn);
    bool isOpen() const { return state == OPEN; }

private:
    State state;
    sf::Font font;
    sf::RectangleShape menuButton;
    sf::Text menuText;

    sf::RectangleShape menuPanel;
    sf::Text musicOnText;
    sf::Text exitGameText;

    sf::FloatRect musicOnBtnRect;
    sf::FloatRect exitGameBtnRect;

    void updatePositions(sf::RenderWindow& window);
};