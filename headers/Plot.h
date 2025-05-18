#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "GameTile.h"
#include "Plant.h"
#include "Wheat.h"
#include "Sheep.h"
#include "Chicken.h"
#include "Barley.h"
#include "Animal.h"
#include "Inventory.h"
#include "Entity.h"

#ifndef PLOT_H
#define PLOT_H


/* Грядка (Plot) — это игровая плитка (GameTile), которая может содержать сущность (например, растение или животное).
   Имеет специальные функции для доступа и изменения этой сущности. */
class Plot : public GameTile
{
protected:
    // Указатель на сущность (растение или животное), размещённую на грядке
    Entity* entity;

public:
    // Конструктор для инициализации объекта Plot
    // Параметры:
    //    texture_filename - имя файла текстуры грядки
    //    pos_x - X-координата позиции
    //    pos_y - Y-координата позиции
    Plot(std::string texture_filename, float pos_x, float pos_y);

    // Разместить растение на грядке
    // Параметры:
    //    _entity - указатель на сущность растения
    // Возвращает: true, если растение успешно размещено, иначе false
    bool placeEntity(Entity* _entity);

    // Очистить грядку (удалить сущность)
    // Возвращает: true, если грядка успешно очищена, иначе false
    bool clear();

    // Собрать урожай с грядки и добавить его в инвентарь
    // Параметры:
    //    inventory - указатель на инвентарь игрока
    // Возвращает: true, если урожай успешно собран и добавлен, иначе false
    bool harvest(Inventory* inventory);

    // Проверить, пуста ли грядка (нет размещённой сущности)
    // Возвращает: true, если грядка пуста, иначе false
    bool isEmpty();

    // Проверить, погибла ли сущность на грядке
    // Возвращает: true, если сущность погибла, иначе false
    bool checkDeath();

    // Полить сущность на грядке
    void water();

    // Удобрить сущность на грядке
    void fertilise(Inventory* Inventory);

    // Покормить животное на грядке
    void feed(Inventory* Inventory);

    // Получить флаг, указывающий, находится ли растение на грядке
    // Возвращает: true, если на грядке растение, иначе false
    bool get_isPlant();

    // Получить флаг, указывающий, находится ли животное на грядке
    // Возвращает: true, если на грядке животное, иначе false
    bool get_isAnimal();

    // Обновить спрайт грядки в зависимости от типа сущности
    // Возвращает: true, если спрайт успешно обновлён, иначе false
    bool updateSprite();

    // Симулировать рост сущности на грядке
    // Возвращает: true, если сущность выросла, иначе false
    bool growEntity();

    // Сбросить грядку (очистить сущность и восстановить спрайт)
    void plotReset();

    // Функция для забоя животных
    void Slaughter(Inventory* Inventory);
};

#endif