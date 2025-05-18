#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "Inventory.h"
#ifndef SHOP_H
#define SHOP_H


/*Магазин - это место, где игрок может покупать и продавать свои ресурсы.
Прогресс в игре достигается по мере заработка денег, что позволяет
торговать более дорогими товарами, например, овцами.*/
class Shop
{
private:
    // Текстура и спрайт фона магазина
    sf::Texture Backdrop_texture;
    sf::Sprite Backdrop_sprite;

    // Флаг, указывающий, открыт ли магазин
    bool shopIsOpen;

    // Позиция магазина
    int shop_pos_x;
    int shop_pos_y;

public:
    // Конструктор для инициализации объекта Shop
    Shop();

    // Геттер для флага открытия магазина
    // Возвращает: true, если магазин открыт, иначе false
    bool get_shopIsOpen();

    // Отображение текста магазина на окне
    // Параметры: window - Указатель на окно рендеринга SFML.
    //            display_string - Текст для отображения.
    //            x - Координата X для позиционирования текста.
    //            y - Координата Y для позиционирования текста.
    void displayShopText(sf::RenderWindow* window, std::string display_string, int x, int y);

    // Сеттер для флага открытия магазина
    // Параметры: _shopIsOpen - Логическое значение, указывающее, открыт ли магазин
    void set_shopIsOpen(bool _shopIsOpen);

    // Открыть магазин и позволить игроку взаимодействовать с ним
    // Параметры: window - Указатель на окно рендеринга SFML.
    //            money - Количество денег у игрока
    // Возвращает: true, если магазин открыт и игрок взаимодействовал, иначе false
    bool shopOpen(sf::RenderWindow* window, int money);

    // Функция для продажи всех товаров в инвентаре
    bool sellGoods(Inventory* Inventory);
};


#endif