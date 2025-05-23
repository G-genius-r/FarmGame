#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>

/*Класс Inventory хранит все ресурсы фермы и определяет,
что игрок может посадить, а что нет. Инвентарь
можно сохранять при выходе из игры.*/
class Inventory
{
private:
    /*Ресурсы*/
    int money;          // Деньги
    int fertiliser;     // Удобрения
    int animalFeed;     // Корм для животных

    /*Товары для продажи*/
    int wheatGrain;     // Зерно пшеницы
    int barleyGrain;   // Зерно ячменя
    int wool;          // Шерсть
    int eggs;          // Яйца
    int meat;          // Мясо

    /*Семена*/
    int wheatSeed;      // Семена пшеницы
    int barleySeed;    // Семена ячменя

    /*Животные*/
    int sheep;         // Овцы
    int chickens;      // Куры

    /*Специфичные для класса Inventory элементы*/
    sf::Texture backdrop_texture;  // Текстура фона инвентаря
    sf::Sprite  backdrop_sprite;   // Спрайт фона инвентаря
    int inventoryPos_x;            // Позиция инвентаря по X
    int inventoryPos_y;            // Позиция инвентаря по Y

public:
    /*Конструктор*/
    Inventory();

    /*Сохранение и загрузка из файла*/
    bool saveDataToFile(const std::string& filename);    // Сохранить данные в файл
    bool loadDataFromFile(const std::string& filename);  // Загрузить данные из файла

    /*Функции для доступа и изменения приватных членов инвентаря*/
    void moneyAdd(int amount);            // Добавить деньги
    bool moneyTake(int amount);           // Списать деньги (если возможно)
    void fertiliserAdd(int amount);       // Добавить удобрения
    bool fertiliserTake(int amount);      // Использовать удобрения (если возможно)
    void wheatGrainAdd(int amount);       // Добавить зерно пшеницы
    bool wheatGrainTake(int amount);      // Использовать зерно пшеницы
    void barleyGrainAdd(int amount);      // Добавить зерно ячменя
    bool barleyGrainTake(int amount);     // Использовать зерно ячменя
    void wheatSeedAdd(int amount);        // Добавить семена пшеницы
    bool wheatSeedTake(int amount);       // Использовать семена пшеницы
    void barleySeedAdd(int amount);       // Добавить семена ячменя
    bool barleySeedTake(int amount);      // Использовать семена ячменя
    void woolAdd(int amount);            // Добавить шерсть
    bool woolTake(int amount);           // Использовать шерсть
    void eggsAdd(int amount);            // Добавить яйца
    bool eggsTake(int amount);          // Использовать яйца
    void ChickenAdd(int amount);        // Добавить кур
    bool ChickenTake(int amount);      // Убрать кур (продать/забить)
    void SheepAdd(int amount);         // Добавить овец
    bool SheepTake(int amount);       // Убрать овец (продать/забить)
    void animalFeedAdd(int amount);    // Добавить корм для животных
    bool animalFeedTake(int amount);   // Использовать корм для животных
    void meatAdd(int amount);         // Добавить мясо
    bool meatTake(int amount);        // Использовать мясо

    // Геттеры для товаров и денег
    unsigned int getMoney();
    int getWool();
    int getEggs();
    int getWheatGrain();
    int getBarleyGrain();
    int getMeat();
    int getFertiliser() { return(fertiliser); };    // Получить количество удобрений
    int getWheatSeed() { return(wheatSeed); };      // Получить количество семян пшеницы
    int getBarleySeed() { return(barleySeed); };    // Получить количество семян ячменя
    int getSheep() { return(sheep); };             // Получить количество овец
    int getChickens() { return(chickens); };       // Получить количество кур

    /*Функции для отображения инвентаря*/
    bool show(sf::RenderWindow* window);                      // Показать инвентарь
    void displayInvText(sf::RenderWindow* window, std::string displayString, int x, int y); // Отобразить текст в инвентаре
};

#endif