#ifndef FARM_H
#define FARM_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "GameTile.h"
#include "Inventory.h"
#include "Plot.h"
#include "Shop.h"

/* Класс Farm представляет виртуальную ферму.
Он служит центральной сущностью, которая инкапсулирует различные функции, связанные с фермой:
-> инвентарь
-> игровые тайлы
-> грядки
*/
class Farm
{
private:
    //* Вспомогательная функция для установки фоновых тайлов фермы.
    void setBackTiles();

    //* Вспомогательная функция для установки начальных грядок на ферме.
    void setPlots();

    //* Количество ячеек сетки по одной стороне фермы (предполагается квадратная ферма).
    int gridLength;

    //* Счетчик для отслеживания дней.
    int dayCounter;

    //текстуры и спрайты для меню помощи
    sf::Texture Help_texture;
    sf::Sprite Help_sprite;
    //координаты меню помощи
    int help_x;
    int help_y;

public:
    //* Указатель на инвентарь игрока в игре.
    Inventory* inventory;

    //* Указатель на внутриигровой магазин для покупки предметов.
    Shop* shop;

    //* 2D вектор для хранения тайлов сетки фермы.
    std::vector<std::vector<GameTile*> > tiles;

    //* 2D вектор для хранения грядок на ферме.
    std::vector<std::vector<Plot*> > plots;

    //* Конструктор для инициализации объекта фермы.
    Farm();

    //* Отображает доступные действия для выбранной грядки на ферме.
    //* Входные параметры: window - окно SFML для отрисовки опций грядки.
    //*                   pos_x - x-координата выбранной грядки.
    //*                   pos_y - y-координата выбранной грядки.
    void getPlotOptions(sf::RenderWindow* window, float pos_x, float pos_y);

    void drawDayCounter(sf::RenderWindow* window);

    //* Отрисовывает тайлы сетки и грядки в игровом окне.
    //* Входной параметр: window - окно SFML для отрисовки макета фермы.
    void drawPlots(sf::RenderWindow* window);

    //* Продвигает игровое время, симулируя течение времени в игре.
    //* Входной параметр: window - окно SFML для отображения эффекта течения времени.
    void passTime(sf::RenderWindow* window);

    //* Приостанавливает игру на num_seconds. -> по сути замораживает игру
    //* Входной параметр: num_seconds - количество секунд для приостановки игры.
    void pause(int num_seconds);

    //* Изменяет фоновый спрайт конкретного тайла на ферме.
    //* Входные параметры: x - x-координата тайла для изменения.
    //*                    y - y-координата тайла для изменения.
    //*                    textureFilename - имя файла новой текстуры для тайла.
    //* Выходное значение: True, если спрайт успешно изменен, false в противном случае.
    bool changeBackSprite(int x, int y, std::string textureFilename);

    //* Отображает текст, связанный с фермой, в игровом окне.
    //* Входные параметры: window - окно SFML для отображения текста.
    //*                    displayString - текст для отображения.
    //*                    x - x-координата для позиционирования текста.
    //*                    y - y-координата для позиционирования текста.
    void displayFarmText(sf::RenderWindow* window, std::string displayString, int x, int y);

    //* Проверяет, является ли выбранный игровой тайл грядкой (для взаимодействия).
    //* Входной параметр: selectedGametile - позиция выбранного игрового тайла.
    //* Выходное значение: True, если выбранный тайл является грядкой, false в противном случае.
    bool selectedTileIsPlot(sf::Vector2f selectedGametile);

    //* Геттер для длины сетки (количество ячеек по одной стороне фермы).
    //* Выходное значение: длина сетки.
    int get_GridLength() { return gridLength; };

    //* Открывает меню, которое предоставляет пользователю информацию об игре при нажатии клавиши h.
    bool get_Help(sf::RenderWindow* window);
};

#endif