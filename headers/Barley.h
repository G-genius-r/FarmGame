#ifndef BARLEY_H
#define BARLEY_H
#include "Plant.h"

// Класс Barley, представляющий ячмень в игре (наследуется от Plant)
class Barley : public Plant
{
private:

    int waterLevelToDisplay = -1;
    sf::Clock waterDisplayClock;

public:
    void showWaterLevel();
    void drawWaterLevel(sf::RenderWindow& window, float x, float y);
    // Конструктор для инициализации объекта Barley
    Barley();

    // Реализация виртуальной функции для получения типа растения
    // Возвращает: тип растения (в данном случае 2 для ячменя)
    int get_type();


    // Реализация виртуальной функции для симуляции роста растения
    // Возвращает: true, если растение выросло, иначе false
    bool grow();

    // Реализация виртуальной функции для полива растения
    void water();

    void draw(sf::RenderWindow& window, float x, float y);

    // Получение максимального уровня полива для ячменя
    // Возвращает: максимальный уровень полива (для ячменя - 4)
    int get_maxWateringLevel() { return(4); };
};

#endif