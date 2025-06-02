#include "../headers/menu.h"
#include <SFML/Audio.hpp>
#include <fstream>

// ������� �������� ��������� ������ ���������
bool loadDefaultInventoryData(const std::string& filename, Farm& farm, NotificationPanel& notifPanel) {
    if (farm.inventory->loadDataFromFile(filename)) {
        notifPanel.addMessage("�����������, ������");
        return true;
    }
    else {
        notifPanel.addMessage("������ �������� ��������� ������ ���������.");
        return false;
    }
}

// ������� �������� ����������� ������ ���������
bool loadInventoryDataFromFile(const std::string& filename, Farm& farm, NotificationPanel& notifPanel) {
    if (farm.inventory->loadDataFromFile(filename)) {
        notifPanel.addMessage("� ������������, ������");
        notifPanel.addMessage("������ ��������� ������� ���������.");
        return true;
    }
    else {
        notifPanel.addMessage("������ �������� ������ ���������.");
        return false;
    }
}

// ������� ��� ����������� ������� �������������
bool showConfirmationDialog(sf::RenderWindow& window, const sf::Font& font, const std::string& message) {
    sf::RectangleShape dialogBox(sf::Vector2f(600, 200));
    dialogBox.setFillColor(sf::Color(50, 50, 50));
    dialogBox.setOutlineColor(sf::Color::White);
    dialogBox.setOutlineThickness(2);
    dialogBox.setPosition(window.getSize().x / 2 - dialogBox.getSize().x / 2,
        window.getSize().y / 2 - dialogBox.getSize().y / 2);

    sf::Text messageText(message, font, 28);
    messageText.setFillColor(sf::Color::White);

    std::vector<std::string> lines;
    size_t pos = 0;
    size_t prev_pos = 0;
    while ((pos = message.find('\n', prev_pos)) != std::string::npos) {
        lines.push_back(message.substr(prev_pos, pos - prev_pos));
        prev_pos = pos + 1;
        if (pos == std::string::npos) break;
    }
    lines.push_back(message.substr(prev_pos));

    sf::Text yesButton("��", font, 32);
    yesButton.setFillColor(sf::Color::White);

    sf::Text noButton("���", font, 32);
    noButton.setFillColor(sf::Color::White);

    float textY = dialogBox.getPosition().y + 30;
    for (const auto& line : lines) {
        messageText.setString(line);
        messageText.setPosition(dialogBox.getPosition().x + dialogBox.getSize().x / 2 - messageText.getGlobalBounds().width / 2,
            textY);
        textY += messageText.getGlobalBounds().height + 10;
    }

    float buttonY = dialogBox.getPosition().y + dialogBox.getSize().y - 60;
    yesButton.setPosition(dialogBox.getPosition().x + dialogBox.getSize().x / 4 - yesButton.getGlobalBounds().width / 2,
        buttonY);
    noButton.setPosition(dialogBox.getPosition().x + 3 * dialogBox.getSize().x / 4 - noButton.getGlobalBounds().width / 2,
        buttonY);

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

        window.draw(dialogBox);

        textY = dialogBox.getPosition().y + 30;
        for (const auto& line : lines) {
            messageText.setString(line);
            messageText.setPosition(dialogBox.getPosition().x + dialogBox.getSize().x / 2 - messageText.getGlobalBounds().width / 2,
                textY);
            window.draw(messageText);
            textY += messageText.getGlobalBounds().height + 10;
        }

        window.draw(yesButton);
        window.draw(noButton);
        window.display();
    }
    return false;
}

// ������� ��� ����������� ���� � ��������� ����
void showRulesWindow(sf::RenderWindow& window, const sf::Font& font) {
    // ������� ���� ������ (90% ������� ��������� ����)
    sf::RectangleShape rulesWindow(sf::Vector2f(window.getSize().x * 0.9f, window.getSize().y * 0.9f));
    rulesWindow.setFillColor(sf::Color(50, 50, 50));
    rulesWindow.setOutlineColor(sf::Color::White);
    rulesWindow.setOutlineThickness(2);
    rulesWindow.setPosition(window.getSize().x * 0.05f, window.getSize().y * 0.05f);

    // ���������
    sf::Text title("������� ����", font, 40);
    title.setFillColor(sf::Color::Yellow);
    title.setStyle(sf::Text::Bold);
    title.setPosition(
        rulesWindow.getPosition().x + rulesWindow.getSize().x / 2 - title.getGlobalBounds().width / 2,
        rulesWindow.getPosition().y + 20
    );

    // ������� ���� (��������� �� ��������� ������)
    std::vector<std::string> rules = {
        "������� 'B' ��� �������� ��������",
        "������� 'I' ��� �������� ���������",
        "������� 'P' ��� �������� �� ��������� ����",
        "�������� ����� �������� ������ ����,",
        "�������� ������ ���� ��� �� �����.",
        "�������� ����� ����� � ������� ���������.",
        "��� ����� ��� ��� ������",
        "����������� ����� '�������'.",
        "���� �������� ��� ��������",
        "�� �������� ���� ��� ��� - ��� ��������.",
        "���� ����� 10 ����, ���� - 15 ����.",
        "���� ������ ���������� 1000 �����.",
        "����� � ����������!"
    };

    // ������� ��������� ������� ��� ������
    std::vector<sf::Text> ruleTexts;
    float yOffset = 80.0f;
    const float lineHeight = 40.0f;

    for (const auto& rule : rules) {
        sf::Text text(rule, font, 28);
        text.setFillColor(sf::Color::White);
        text.setPosition(
            rulesWindow.getPosition().x + 30.0f,
            rulesWindow.getPosition().y + yOffset
        );
        ruleTexts.push_back(text);
        yOffset += lineHeight;
    }

    // ������ ��������
    sf::Text closeButton("������� (Esc)", font, 32);
    closeButton.setFillColor(sf::Color::White);
    closeButton.setPosition(
        rulesWindow.getPosition().x + rulesWindow.getSize().x / 2 - closeButton.getGlobalBounds().width / 2,
        rulesWindow.getPosition().y + rulesWindow.getSize().y - 60.0f
    );

    // �������� ���� ���� ������
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                return;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

                if (closeButton.getGlobalBounds().contains(worldPos)) {
                    return;
                }
            }
        }

        window.clear();
        window.draw(rulesWindow);
        window.draw(title);

        for (auto& text : ruleTexts) {
            window.draw(text);
        }

        window.draw(closeButton);
        window.display();
    }
}

// �������� ������� ����
bool showMenu(sf::RenderWindow& window, bool& musicOn, Farm& farm, NotificationPanel& notifPanel) {
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

    if (musicOn) music.play();
    else music.pause();

    // ������-������� ��� ��������� ������ � ��������
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

    const unsigned int menuFontSize = 48;
    bool hasSavedData = std::ifstream("InventoryData.txt").good();

    // ������� ������ ����
    sf::Text newGameButton("����� ����", font, menuFontSize);
    newGameButton.setFillColor(sf::Color::White);

    sf::Text playButton(hasSavedData ? "���������� ����" : "������ ����� ����", font, menuFontSize);
    playButton.setFillColor(sf::Color::White);

    sf::Text rulesButton("������� ����", font, menuFontSize);
    rulesButton.setFillColor(sf::Color::White);

    sf::Text musicButton("", font, menuFontSize);
    musicButton.setFillColor(sf::Color::White);

    sf::Text exitButton("�����", font, menuFontSize);
    exitButton.setFillColor(sf::Color::White);

    // ������� ��� ������������� ������
    auto centerButtons = [&]() {
        float w = window.getSize().x;
        float startY = 300.0f;
        float spacing = 60.0f;

        newGameButton.setPosition(w / 2.0f - newGameButton.getGlobalBounds().width / 2.0f, startY);
        playButton.setPosition(w / 2.0f - playButton.getGlobalBounds().width / 2.0f,
            newGameButton.getPosition().y + newGameButton.getGlobalBounds().height + spacing);
        rulesButton.setPosition(w / 2.0f - rulesButton.getGlobalBounds().width / 2.0f,
            playButton.getPosition().y + playButton.getGlobalBounds().height + spacing);
        musicButton.setPosition(w / 2.0f - musicButton.getGlobalBounds().width / 2.0f,
            rulesButton.getPosition().y + rulesButton.getGlobalBounds().height + spacing);
        exitButton.setPosition(w / 2.0f - exitButton.getGlobalBounds().width / 2.0f,
            musicButton.getPosition().y + musicButton.getGlobalBounds().height + spacing);
        };

    // ������� ��� ���������� ������ ������ ������
    auto updateMusicButton = [&]() {
        musicButton.setString(musicOn ? "������: ���" : "������: ����");
        centerButtons();
        };

    updateMusicButton();

    // �������� ���� ����
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

                if (newGameButton.getGlobalBounds().contains(worldPos.x, worldPos.y)) {
                    bool confirmed = showConfirmationDialog(window, font,
                        "�� ����� ������ ������ ����� ����?\n��� ���� ������� ������ ����� ������.");
                    if (confirmed) {
                        music.stop();
                        return loadDefaultInventoryData("InventoryDataZero.txt", farm, notifPanel);
                    }
                }
                else if (playButton.getGlobalBounds().contains(worldPos.x, worldPos.y)) {
                    music.stop();
                    return loadInventoryDataFromFile("InventoryData.txt", farm, notifPanel);
                }
                else if (rulesButton.getGlobalBounds().contains(worldPos.x, worldPos.y)) {
                    showRulesWindow(window, font);
                }
                else if (musicButton.getGlobalBounds().contains(worldPos.x, worldPos.y)) {
                    musicOn = !musicOn;
                    if (musicOn) music.play();
                    else music.pause();
                    updateMusicButton();
                }
                else if (exitButton.getGlobalBounds().contains(worldPos.x, worldPos.y)) {
                    window.close();
                    return false;
                }
            }
        }

        window.clear();
        window.draw(background);
        drawTextWithOutline(newGameButton);
        drawTextWithOutline(playButton);
        drawTextWithOutline(rulesButton);
        drawTextWithOutline(musicButton);
        drawTextWithOutline(exitButton);
        window.display();
    }
    return false;
}