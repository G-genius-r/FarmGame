#include "../headers/menu.h"

bool showMenu(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("Silkscreen/CyrilicOld.ttf")) {
        return false;
    }

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("sprites/menuBackground.png")) {
        return false;
    }

    sf::Sprite background(backgroundTexture);
    background.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    sf::Music music;
    if (!music.openFromFile("audio/menuMusic.ogg")) {
        return false;
    }
    music.setLoop(true);
    music.play();

    bool musicOn = true;

    auto drawTextWithOutline = [&](sf::Text& text) {
        sf::Text outline = text;
        outline.setFillColor(sf::Color(81, 39, 5, 255));
        for (int dx = -6; dx <= 6; dx++) {
            for (int dy = -2; dy <= 2; dy++) {
                if (dx == 0 && dy == 0) continue;
                outline.setPosition(text.getPosition().x + dx, text.getPosition().y + dy);
                window.draw(outline);
            }
        }
        window.draw(text);
        };

    // Увеличиваем размер шрифта
    const unsigned int menuFontSize = 48;

    sf::Text playButton("Начать игру", font, menuFontSize);
    playButton.setFillColor(sf::Color::White);

    sf::Text musicButton("Музыка: Вкл", font, menuFontSize);
    musicButton.setFillColor(sf::Color::White);

    sf::Text exitButton("Выйти", font, menuFontSize);
    exitButton.setFillColor(sf::Color::White);

    // Новые значения для Y и расстояния между кнопками
    auto centerButtons = [&]() {
        float w = window.getSize().x;
        float startY = 350.0f;
        float spacing = 60.0f; // расстояние между кнопками

        playButton.setPosition(w / 2.0f - playButton.getGlobalBounds().width / 2.0f, startY);
        musicButton.setPosition(w / 2.0f - musicButton.getGlobalBounds().width / 2.0f,
            playButton.getPosition().y + playButton.getGlobalBounds().height + spacing);
        exitButton.setPosition(w / 2.0f - exitButton.getGlobalBounds().width / 2.0f,
            musicButton.getPosition().y + musicButton.getGlobalBounds().height + spacing);
        };

    auto updateMusicButton = [&]() {
        musicButton.setString(musicOn ? "Музыка: Вкл" : "Музыка: Выкл");
        centerButtons();
        };

    updateMusicButton();

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

                if (playButton.getGlobalBounds().contains(worldPos.x, worldPos.y)) {
                    return true;
                }
                else if (exitButton.getGlobalBounds().contains(worldPos.x, worldPos.y)) {
                    window.close();
                    return false;
                }
                else if (musicButton.getGlobalBounds().contains(worldPos.x, worldPos.y)) {
                    musicOn = !musicOn;
                    if (musicOn) music.play();
                    else music.pause();
                    updateMusicButton();
                }
            }
        }

        window.clear();
        window.draw(background);
        drawTextWithOutline(playButton);
        drawTextWithOutline(musicButton);
        drawTextWithOutline(exitButton);
        window.display();
    }
    return false;
}