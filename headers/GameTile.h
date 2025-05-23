#pragma once
#ifndef GAMETILE_H
#define GAMETILE_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>

/*Ферма/игра разделена на сетку 10x10. Каждая клетка представлена объектом GameTile.
GameTile - это базовый графический элемент, на котором строится всё остальное, будь то грядки или другие объекты.*/
class GameTile
{
protected:
    // Текстура и спрайт для рамки выделения, связанной с клеткой
    sf::Texture selectionBoxTexture;
    sf::Sprite selectionBoxSprite;

    // Позиция клетки
    sf::Vector2f pos;

    // Текстура и спрайт для фона клетки
    sf::Texture backTexture;
    sf::Sprite backSprite;

    // Текстура и спрайт для переднего плана клетки
    sf::Texture frontTexture;
    sf::Sprite frontSprite;

public:
    // Конструктор по умолчанию для инициализации объекта GameTile
    GameTile();

    // Конструктор для инициализации объекта GameTile с указанной текстурой фона и позицией
    // Входные параметры: backTextureFilename - имя файла текстуры фона.
    //                   pos_x - X-координата позиции.
    //                   pos_y - Y-координата позиции.
    GameTile(std::string backTextureFilename, float pos_x, float pos_y);

    // Настройка спрайта фона клетки с использованием указанного файла текстуры
    // Входные параметры: backTextureFilename - имя файла текстуры фона.
    // Возвращаемое значение: true, если спрайт фона успешно настроен, иначе false.
    bool setUpBackSprite(std::string backTextureFilename);

    // Настройка спрайта фона клетки с использованием указанного файла текстуры и позиции
    // Входные параметры: backTextureFilename - имя файла текстуры фона.
    //                   pos_x - X-координата позиции.
    //                   pos_y - Y-координата позиции.
    // Возвращаемое значение: true, если спрайт фона успешно настроен, иначе false.
    bool setUpBackSprite(std::string backTextureFilename, int pos_x, int pos_y);

    // Настройка спрайта переднего плана клетки с использованием указанного файла текстуры
    // Входные параметры: frontTextureFilename - имя файла текстуры переднего плана.
    // Возвращаемое значение: true, если спрайт переднего плана успешно настроен, иначе false.
    bool setUpFrontSprite(std::string frontTextureFilename);

    // Настройка спрайта переднего плана клетки с использованием указанного файла текстуры и позиции
    // Входные параметры: frontTextureFilename - имя файла текстуры переднего плана.
    //                    pos_x - X-координата позиции.
    //                    pos_y - Y-координата позиции.
    // Возвращаемое значение: true, если спрайт переднего плана успешно настроен, иначе false.
    bool setUpFrontSprite(std::string frontTextureFilename, float cellWidth, float cellHeight);

    // Отрисовка рамки выделения на клетке с использованием предоставленного окна
    // Входные параметры: window - указатель на окно рендеринга SFML.
    void drawSelectionBox(sf::RenderWindow* window);

    // Установка позиции клетки
    // Входные параметры: pos_x - X-координата новой позиции.
    //                    pos_y - Y-координата новой позиции.
    void set_pos(float pos_x, float pos_y);

    void setScale(float width, float height);

    // Получение позиции клетки
    // Возвращаемое значение: позиция клетки в виде 2D вектора.
    sf::Vector2f get_pos();

    // Геттер для текстуры фона клетки
    // Возвращаемое значение: текстура фона клетки.
    sf::Texture get_backTexture() { return backTexture; };

    // Геттер для спрайта фона клетки
    // Возвращаемое значение: спрайт фона клетки.
    sf::Sprite get_backSprite() { return backSprite; };

    // Геттер для текстуры переднего плана клетки
    // Возвращаемое значение: текстура переднего плана клетки.
    sf::Texture get_frontTexture() { return frontTexture; };

    // Геттер для спрайта переднего плана клетки
    // Возвращаемое значение: спрайт переднего плана клетки.
    sf::Sprite get_frontSprite() { return frontSprite; };
};
#endif