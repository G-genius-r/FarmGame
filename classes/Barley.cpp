#include "../headers/Barley.h"
#include <iostream>

#define BARLEYWATER 4

// Функция для получения типа растения (унаследовано от класса Plant)
int Barley::get_type()
{
    return 2; // Возвращает тип для ячменя
}

// Конструктор класса Barley
Barley::Barley()
{
    growthStage = 0;      // Инициализация стадии роста значением 0
    wateringLevel = 0;    // Инициализация уровня полива значением 0
    isFertilised = false; // Инициализация состояния удобрения значением false
    

    // Инициализация названий текстур для разных стадий роста и уровней полива
    textureFilenames.push_back("sprites/barleySprite/barley0.png");
    textureFilenames.push_back("sprites/barleySprite/barley1.png");
    textureFilenames.push_back("sprites/barleySprite/barley2.png");
    textureFilenames.push_back("sprites/barleySprite/barley3.png");
    textureFilenames.push_back("sprites/barleySprite/barley0watered.png");
    textureFilenames.push_back("sprites/barleySprite/barley1watered.png");
    textureFilenames.push_back("sprites/barleySprite/barley2watered.png");
    textureFilenames.push_back("sprites/barleySprite/barley3watered.png");

    std::cout << "Растение ячменя создано." << std::endl; // Вывод сообщения о создании
}

// Функция для симуляции роста ячменя
bool Barley::grow()
{
    /* Условия для роста */
    if (growthStage < 3 && wateringLevel == BARLEYWATER && isFertilised)
    {
        growthStage++;
        wateringLevel--;
        std::cout << "Растение ячменя выросло на следующую стадию!" << std::endl;
        return true; // Возвращает true при успешном росте
    }
    else if (growthStage == 3)
        std::cout << "Растение ячменя достигло максимальной стадии роста!" << std::endl;

    return false; // Возвращает false, если условия роста не выполнены
}

// Функция для симуляции полива ячменя
void Barley::water()
{
    if (wateringLevel < BARLEYWATER)
    {
        wateringLevel++;
        showWaterLevel();
    }
    // В любом случае показываем уровень влаги над растением
    waterLevelToDisplay = wateringLevel;
    waterDisplayClock.restart();
}

void Barley::showWaterLevel() {
    waterLevelToDisplay = wateringLevel;
    waterDisplayClock.restart();
}

void Barley::drawWaterLevel(sf::RenderWindow& window, float x, float y) {
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
