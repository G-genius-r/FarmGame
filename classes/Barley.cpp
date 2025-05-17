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
        std::cout << "Растение ячменя полито. Уровень влаги: " << wateringLevel << std::endl;
        return;
    }
    else
    {
        std::cout << "Уровень влаги = " << wateringLevel << " (ячмень уже полит)" << std::endl;
        return;
    }
}