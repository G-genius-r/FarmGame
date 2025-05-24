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

/* ����� Farm ������������ ����������� �����.
�� ������ ����������� ���������, ������� ������������� ��������� �������, ��������� � ������:
-> ���������
-> ������� �����
-> ������
*/
class Farm
{
private:
    //* ��������������� ������� ��� ��������� ������� ������ �����.
    void setBackTiles();

    //* ��������������� ������� ��� ��������� ��������� ������ �� �����.
    void setPlots();

    //* ���������� ����� ����� �� ����� ������� ����� (�������������� ���������� �����).
    int gridLength;

    //* ������� ��� ������������ ����.
    int dayCounter;

    //�������� � ������� ��� ���� ������
    sf::Texture Help_texture;
    sf::Sprite Help_sprite;
    //���������� ���� ������
    int help_x;
    int help_y;

public:
    //* ��������� �� ��������� ������ � ����.
    Inventory* inventory;

    //* ��������� �� ������������� ������� ��� ������� ���������.
    Shop* shop;

    //* 2D ������ ��� �������� ������ ����� �����.
    std::vector<std::vector<GameTile*> > tiles;

    //* 2D ������ ��� �������� ������ �� �����.
    std::vector<std::vector<Plot*> > plots;

    //* ����������� ��� ������������� ������� �����.
    Farm();

    //* ���������� ��������� �������� ��� ��������� ������ �� �����.
    //* ������� ���������: window - ���� SFML ��� ��������� ����� ������.
    //*                   pos_x - x-���������� ��������� ������.
    //*                   pos_y - y-���������� ��������� ������.
    void getPlotOptions(sf::RenderWindow* window, float pos_x, float pos_y);

    void drawDayCounter(sf::RenderWindow* window);

    //* ������������ ����� ����� � ������ � ������� ����.
    //* ������� ��������: window - ���� SFML ��� ��������� ������ �����.
    void drawPlots(sf::RenderWindow* window);

    //* ���������� ������� �����, ��������� ������� ������� � ����.
    //* ������� ��������: window - ���� SFML ��� ����������� ������� ������� �������.
    void passTime(sf::RenderWindow* window);

    //* ���������������� ���� �� num_seconds. -> �� ���� ������������ ����
    //* ������� ��������: num_seconds - ���������� ������ ��� ������������ ����.
    void pause(int num_seconds);

    //* �������� ������� ������ ����������� ����� �� �����.
    //* ������� ���������: x - x-���������� ����� ��� ���������.
    //*                    y - y-���������� ����� ��� ���������.
    //*                    textureFilename - ��� ����� ����� �������� ��� �����.
    //* �������� ��������: True, ���� ������ ������� �������, false � ��������� ������.
    bool changeBackSprite(int x, int y, std::string textureFilename);

    //* ���������� �����, ��������� � ������, � ������� ����.
    //* ������� ���������: window - ���� SFML ��� ����������� ������.
    //*                    displayString - ����� ��� �����������.
    //*                    x - x-���������� ��� ���������������� ������.
    //*                    y - y-���������� ��� ���������������� ������.
    void displayFarmText(sf::RenderWindow* window, std::string displayString, int x, int y);

    //* ���������, �������� �� ��������� ������� ���� ������� (��� ��������������).
    //* ������� ��������: selectedGametile - ������� ���������� �������� �����.
    //* �������� ��������: True, ���� ��������� ���� �������� �������, false � ��������� ������.
    bool selectedTileIsPlot(sf::Vector2f selectedGametile);

    //* ������ ��� ����� ����� (���������� ����� �� ����� ������� �����).
    //* �������� ��������: ����� �����.
    int get_GridLength() { return gridLength; };

    //* ��������� ����, ������� ������������� ������������ ���������� �� ���� ��� ������� ������� h.
    bool get_Help(sf::RenderWindow* window);
};

#endif