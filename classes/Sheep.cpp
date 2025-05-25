#include "../headers/Sheep.h"
#include <iostream>

// Конструктор класса Sheep
Sheep::Sheep() {
    wool = false;
    growthStage = 0;
    lifespan = 20;
    textureFilenames.push_back("./sprites/sheepSprite/sheepShornSprite.png");
    textureFilenames.push_back("./sprites/sheepSprite/sheepSprite.png");
    isAnimal = true;
    hungryStatus = 0;
    wateringLevel = 0;
    waterLevelToDisplay = -1;
}

// Производство шерсти
void Sheep::produceWool() {
    wool = true;
    std::cout << "Овца отрастила шерсть" << std::endl;
}

// Проверка наличия шерсти
bool Sheep::getWool() {
    return wool;
}

// Установка статуса шерсти
void Sheep::setWool(bool _wool) {
    wool = _wool;
}

// Получение типа животного
int Sheep::get_type() {
    return 4;
}

// Рост овцы
bool Sheep::grow() {
    if (wateringLevel == 3 && hungryStatus == 3 && !wool) {
        produceWool();
    }

    wateringLevel--;
    if (wateringLevel < 0) wateringLevel = 0;

    hungryStatus--;
    if (hungryStatus < 0) hungryStatus = 0;

    growthStage++;
    std::cout << "Овца выросла до возраста: " << growthStage << std::endl;
    return true;
}

// Полив овцы
void Sheep::water() {
    if (wateringLevel < 3) {
        wateringLevel++;
        showWaterLevel();
    }
    waterLevelToDisplay = wateringLevel;
    waterDisplayClock.restart();
}

// Показать уровень воды
void Sheep::showWaterLevel() {
    waterLevelToDisplay = wateringLevel;
    waterDisplayClock.restart();
}

// Отрисовка уровня воды
void Sheep::drawWaterLevel(sf::RenderWindow& window, float x, float y) {
    if (waterLevelToDisplay != -1 && waterDisplayClock.getElapsedTime().asSeconds() < 1.0f) {
        static sf::Font font;
        static bool fontLoaded = false;
        if (!fontLoaded) {
            if (font.loadFromFile("Silkscreen/CyrilicOld.ttf")) {
                fontLoaded = true;
            }
        }
        if (fontLoaded) {
            sf::Text txt("Вода: " + std::to_string(wateringLevel), font, 20);
            txt.setFillColor(sf::Color::Blue);
            txt.setPosition(x, y - 25);
            window.draw(txt);
        }
    }
    else if (waterLevelToDisplay != -1) {
        waterLevelToDisplay = -1;
    }
}