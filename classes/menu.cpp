#include "../headers/menu.h"
#include <SFML/Audio.hpp>
#include <fstream>
#include <string>
#include <windows.h> // Для ShellExecute
#include <shlwapi.h> // Для PathRemoveFileSpec
#pragma comment(lib, "shlwapi.lib")

// Функция загрузки начальных данных инвентаря
bool loadDefaultInventoryData(const std::string& filename, Farm& farm, NotificationPanel& notifPanel) {
    if (farm.startNewGame()) {
        notifPanel.addMessage("Приветствую, фермер");
        return true;
    }
    else {
        notifPanel.addMessage("Ошибка запуска новой игры.");
        return false;
    }
}

// Функция загрузки сохраненных данных инвентаря
bool loadInventoryDataFromFile(const std::string& filename, Farm& farm, NotificationPanel& notifPanel) {
    if (farm.loadFromFiles("GameData.txt", "InventoryData.txt")) {
        notifPanel.addMessage("С возвращением, фермер");
        notifPanel.addMessage("Данные инвентаря успешно загружены.");
        return true;
    }
    else {
        notifPanel.addMessage("Ошибка загрузки данных инвентаря.");
        return false;
    }
}

// Функция для отображения диалога подтверждения
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

    sf::Text yesButton("Да", font, 32);
    yesButton.setFillColor(sf::Color::White);

    sf::Text noButton("Нет", font, 32);
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

// Функция для открытия файла справки (только для Windows)
void openHelpFile() {
    // 1. Получаем путь к исполняемому файлу
    char exePath[MAX_PATH] = { 0 };
    GetModuleFileNameA(NULL, exePath, MAX_PATH);

    // 2. Удаляем имя файла, оставляя только путь к директории
    PathRemoveFileSpecA(exePath);

    // 3. Формируем полный путь к файлу справки
    std::string helpFile = std::string(exePath) + "\\HelpSystem\\СправкаПомощи.chm";

    // 4. Проверяем существование файла
    if (GetFileAttributesA(helpFile.c_str()) == INVALID_FILE_ATTRIBUTES) {
        MessageBoxA(NULL, ("Файл справки не найден по пути:\n" + helpFile).c_str(),
            "Ошибка", MB_ICONERROR);
        return;
    }

    // 5. Пытаемся открыть
    HINSTANCE result = ShellExecuteA(
        NULL,
        "open",
        "hh.exe",
        helpFile.c_str(),
        NULL,
        SW_SHOWNORMAL
    );

    // 6. Проверяем результат
    if ((int)result <= 32) {
        std::string errorMsg = "Не удалось открыть файл справки.\n";
        errorMsg += "Код ошибки: " + std::to_string((int)result) + "\n";
        errorMsg += "Путь: " + helpFile;

        MessageBoxA(NULL, errorMsg.c_str(), "Ошибка", MB_ICONERROR);
    }
}

// Основная функция меню
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

    // Лямбда-функция для отрисовки текста с обводкой
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

    // Создаем кнопки меню
    sf::Text newGameButton("Новая игра", font, menuFontSize);
    newGameButton.setFillColor(sf::Color::White);

    sf::Text playButton("Продолжить игру", font, menuFontSize);
    playButton.setFillColor(hasSavedData ? sf::Color::White : sf::Color(150, 150, 150)); // Серый цвет, если нет сохранений

    sf::Text helpButton("Справка", font, menuFontSize);
    helpButton.setFillColor(sf::Color::White);

    sf::Text musicButton("", font, menuFontSize);
    musicButton.setFillColor(sf::Color::White);

    sf::Text exitButton("Выйти", font, menuFontSize);
    exitButton.setFillColor(sf::Color::White);

    // Функция для центрирования кнопок
    auto centerButtons = [&]() {
        float w = window.getSize().x;
        float startY = 300.0f;
        float spacing = 60.0f;

        newGameButton.setPosition(w / 2.0f - newGameButton.getGlobalBounds().width / 2.0f, startY);
        playButton.setPosition(w / 2.0f - playButton.getGlobalBounds().width / 2.0f,
            newGameButton.getPosition().y + newGameButton.getGlobalBounds().height + spacing);
        helpButton.setPosition(w / 2.0f - helpButton.getGlobalBounds().width / 2.0f,
            playButton.getPosition().y + playButton.getGlobalBounds().height + spacing);
        musicButton.setPosition(w / 2.0f - musicButton.getGlobalBounds().width / 2.0f,
            helpButton.getPosition().y + helpButton.getGlobalBounds().height + spacing);
        exitButton.setPosition(w / 2.0f - exitButton.getGlobalBounds().width / 2.0f,
            musicButton.getPosition().y + musicButton.getGlobalBounds().height + spacing);
        };

    // Функция для обновления текста кнопки музыки
    auto updateMusicButton = [&]() {
        musicButton.setString(musicOn ? "Музыка: Вкл" : "Музыка: Выкл");
        centerButtons();
        };

    updateMusicButton();

    // Основной цикл меню
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
                        "Вы точно хотите начать новую игру?\nВсе ваши прошлые данные будут стерты.");
                    if (confirmed) {
                        music.stop();
                        return loadDefaultInventoryData("InventoryDataZero.txt", farm, notifPanel);
                    }
                }
                else if (playButton.getGlobalBounds().contains(worldPos.x, worldPos.y) && hasSavedData) {
                    music.stop();
                    return loadInventoryDataFromFile("InventoryData.txt", farm, notifPanel);
                }
                else if (helpButton.getGlobalBounds().contains(worldPos.x, worldPos.y)) {
                    openHelpFile();
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
        drawTextWithOutline(helpButton);
        drawTextWithOutline(musicButton);
        drawTextWithOutline(exitButton);
        window.display();
    }
    return false;
}