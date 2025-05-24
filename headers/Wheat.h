#ifndef WHEAT_H
#define WHEAT_H
#include "Plant.h"

// Класс Wheat, представляющий пшеницу в игре (наследуется от Plant)
class Wheat : public Plant
{
private:

    int waterLevelToDisplay = -1;
    sf::Clock waterDisplayClock;
    // В private-секции:
    sf::Texture waterTexture;
    sf::Sprite waterSprite;

public:
    void showWaterLevel();
    void drawWaterLevel(sf::RenderWindow& window, float x, float y);
    // Конструктор для инициализации объекта Wheat
    Wheat();

    // Реализация виртуальной функции для получения типа растения
    // Возвращает: тип растения (в данном случае 1 для пшеницы)
    int get_type();

    // Реализация виртуальной функции для симуляции роста растения
    // Возвращает: true, если растение выросло, иначе false
    bool grow();

    // Реализация виртуальной функции для полива растения
    void water();

    void draw(sf::RenderWindow& window, float x, float y);

    // Получение максимального уровня полива для пшеницы
    // Возвращает: максимальный уровень полива (для пшеницы - 5)
    int get_maxWateringLevel() { return(5); };
};

#endif