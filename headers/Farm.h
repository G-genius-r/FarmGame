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
#include <memory>
#include "Button.h"
#include "NotificationPanel.h"
#include "GameState.h"

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

public:    
    Farm();

    void setNotificationPanel(NotificationPanel* panel);

    void setDay(int d) { dayCounter = d; }
    int getDay() const { return dayCounter; }

    Shop* shop;
    Inventory* inventory;
    int help_x, help_y;

    std::vector<std::vector<class Plot*>> plots;
    std::vector<std::vector<class GameTile*>> tiles;

    std::vector<std::unique_ptr<Button>> plotOptionButtons;

    void createPlotOptionButtons(int plotX, int plotY, NotificationPanel* notifPanel);
    void drawPlotOptionButtons(sf::RenderWindow* window);

    void drawHungerSprites(sf::RenderWindow* window);

    void clearPlotOptionButtons();
    int getGridLength() const;

    bool saveToFiles(const std::string& gameDataFilename, const std::string& inventoryFilename);
    bool loadFromFiles(const std::string& gameDataFilename, const std::string& inventoryFilename);

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

    bool handlePlotOptionButtonsEvent(const sf::Event& event, const sf::Vector2f& mousePos);

    //* ���������� �����, ��������� � ������, � ������� ����.
    //* ������� ���������: window - ���� SFML ��� ����������� ������.
    //*                    displayString - ����� ��� �����������.
    //*                    x - x-���������� ��� ���������������� ������.
    //*                    y - y-���������� ��� ���������������� ������.
    void displayFarmText(sf::RenderWindow* window, std::string displayString, int x, int y);

    void drawFertiliserSprites(sf::RenderWindow* window);

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