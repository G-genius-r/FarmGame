#pragma once
#ifndef CHICKEN_H
#define CHICKEN_H

#include "Animal.h"
#include <SFML/Graphics.hpp>

// Класс Chicken (Курица), наследуемый от Animal
class Chicken : public Animal
{
private:
    int eggs; // Количество яиц у курицы
    int waterLevelToDisplay; // Текущий уровень воды для отображения
    sf::Clock waterDisplayClock; // Таймер для отображения уровня воды

public:
    // Конструктор класса Chicken
    Chicken();

    // Отложить яйцо
    // Возвращает: true если успешно, false если достигнут максимум яиц
    bool layEgg();

    // Получить текущее количество яиц
    int getEggs();

    // Установить количество яиц
    // Параметр: _eggs - количество яиц для установки
    void setEggs(int _eggs);

    // Получить тип сущности (переопределение виртуальной функции)
    // Возвращает: тип курицы (константное значение)
    int get_type() override;

    // Симулировать рост курицы (переопределение виртуальной функции)
    // Возвращает: true если рост произошел
    bool grow() override;

    // Полить курицу (переопределение виртуальной функции)
    void water() override;

    // Показать уровень воды
    void showWaterLevel();

    // Отрисовать уровень воды
    // Параметры:
    // window - окно для отрисовки
    // x, y - координаты для отрисовки
    void drawWaterLevel(sf::RenderWindow& window, float x, float y);

    // Получить максимальный уровень полива
    // Возвращает: 3 (максимальный уровень полива для курицы)
    int get_maxWateringLevel() override { return 3; };

    // Деструктор класса Chicken
    ~Chicken() {};
};

#endif