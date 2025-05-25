#pragma once
#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include "Entity.h"
#include "Inventory.h"

// Класс Animal, наследуемый от Entity, представляет базовый класс для всех животных в игре
class Animal : public Entity
{
protected:
    // Тип животного (например, "курица", "овца")
    std::string type;

    // Продолжительность жизни животного (в днях)
    int lifespan;

    // Текстуры, связанные с животным
    std::vector<std::string> textures;

public:
    // Уровень сытости животного (уменьшается каждый день)
    int hungryStatus;

    // Конструктор для инициализации объекта Animal
    Animal();

    // Проверяет, умерло ли животное
    // Возвращает: true, если животное умерло, иначе false
    bool checkDeath();

    // Кормит животное зерном из инвентаря
    // Параметр: Inventory - указатель на инвентарь
    // Возвращает: true, если животное успешно накормлено, иначе false
    bool eatGrain(Inventory* Inventory);

    // Получает текущий возраст животного
    // Возвращает: возраст животного
    int get_age();

    // Устанавливает возраст животного
    // Параметр: _age - возраст для установки
    void set_age(int _age);

    // Виртуальная функция для получения типа животного (должна быть реализована в производных классах)
    // Возвращает: тип животного (например, 1 - курица, 2 - овца)
    virtual int get_type() = 0;

    // Получает продолжительность жизни животного
    // Возвращает: продолжительность жизни
    int get_lifespan();

    // Устанавливает продолжительность жизни животного
    // Параметр: _lifespan - продолжительность жизни для установки
    void set_lifespan(int _lifespan);

    // Получает текущий уровень сытости животного
    // Возвращает: уровень сытости
    int get_hungryStatus();

    // Устанавливает уровень сытости животного
    // Параметр: _hungryStatus - уровень сытости для установки
    void set_hungryStatus(int _hungryStatus);

    // Виртуальная функция для роста животного (должна быть реализована в производных классах)
    virtual bool grow() = 0;

    std::string getHungerSprite() const;

    // Деструктор класса Animal
    ~Animal();
};

#endif