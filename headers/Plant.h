#pragma once

#ifndef PLANT_H
#define PLANT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "Entity.h"
#include "Inventory.h"

class Plant : public Entity
{
protected:
    // Флаг, указывающий, было ли растение удобрено
    bool isFertilised;

public:
    // Конструктор для инициализации объекта Plant
    Plant();

    // Функция для удобрения растения
    void fertilise(Inventory* Inventory);

    // Функция для проверки, погибло ли растение
    // Возвращает: true, если растение погибло, иначе false
    bool checkDeath();

    // Функция для получения корректного имени файла текстуры растения
    // Возвращает: корректное имя файла текстуры растения
    std::string getCorrectFilename();

    // Виртуальная функция для получения типа растения (должна быть реализована в производных классах)
    // Возвращает: тип растения (например, 1 — Пшеница, 2 — Ячмень и т. д.)
    virtual int get_type() = 0;

    // Виртуальная функция для симуляции роста растения (должна быть реализована в производных классах)
    // Возвращает: true, если растение выросло, иначе false
    virtual bool grow() = 0;
};

#endif