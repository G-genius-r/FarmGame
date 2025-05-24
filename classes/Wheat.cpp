#include "../headers/Wheat.h"
#include <iostream>

#define WHEATWATER 5

// Функция для получения типа растения (унаследовано от класса Plant)
int Wheat::get_type()
{
    return 1; // Возвращает тип для пшеницы
}

// Конструктор класса Wheat
Wheat::Wheat()
{
    growthStage = 0;      // Инициализация стадии роста значением 0
    wateringLevel = 0;    // Инициализация уровня полива значением 0
    isFertilised = false; // Инициализация состояния удобрения значением false

    // Инициализация названий текстур для разных стадий роста и уровней полива
    textureFilenames.push_back("sprites/wheatSprite/wheat0.png");
    textureFilenames.push_back("sprites/wheatSprite/wheat1.png");
    textureFilenames.push_back("sprites/wheatSprite/wheat2.png");
    textureFilenames.push_back("sprites/wheatSprite/wheat3.png");
    textureFilenames.push_back("sprites/wheatSprite/wheat0watered.png");
    textureFilenames.push_back("sprites/wheatSprite/wheat1watered.png");
    textureFilenames.push_back("sprites/wheatSprite/wheat2watered.png");
    textureFilenames.push_back("sprites/wheatSprite/wheat3watered.png");

    std::cout << "Растение пшеницы создано." << std::endl; // Сообщение о создании
}

// Функция для симуляции роста пшеницы
bool Wheat::grow()
{
    /* Условия для роста */
    if (growthStage < 3 && wateringLevel == WHEATWATER && isFertilised)
    {
        growthStage++;
        wateringLevel--;
        std::cout << "Растение пшеницы выросло на следующую стадию!" << std::endl;
        return true; // Возвращает true при успешном росте
    }
    else if (growthStage == 3)
        std::cout << "Растение пшеницы достигло максимальной стадии роста!" << std::endl;

    return false; // Возвращает false, если условия роста не выполнены
}

// Функция для симуляции полива пшеницы
void Wheat::water()
{
    if (wateringLevel < WHEATWATER)
    {
        wateringLevel++;
        showWaterLevel();
    }
    // В любом случае показываем уровень влаги над растением
    waterLevelToDisplay = wateringLevel;
    waterDisplayClock.restart();
}

void Wheat::showWaterLevel() {
    waterLevelToDisplay = wateringLevel;
    waterDisplayClock.restart();
}

void Wheat::drawWaterLevel(sf::RenderWindow& window, float x, float y) {
    if (waterLevelToDisplay != -1 && waterDisplayClock.getElapsedTime().asSeconds() < 1.0f) {
        static sf::Font font;
        static bool fontLoaded = false;
        if (!fontLoaded) {
            font.loadFromFile("Silkscreen/CyrilicOld.ttf");
            fontLoaded = true;
        }
        sf::Text txt("Влага: " + std::to_string(wateringLevel), font, 20);
        txt.setFillColor(sf::Color::Blue);
        txt.setPosition(x, y - 25);
        window.draw(txt);
    }
    else if (waterLevelToDisplay != -1) {
        waterLevelToDisplay = -1;
    }
}