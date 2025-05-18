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


/* ������ (Plot) � ��� ������� ������ (GameTile), ������� ����� ��������� �������� (��������, �������� ��� ��������).
   ����� ����������� ������� ��� ������� � ��������� ���� ��������. */
class Plot : public GameTile
{
protected:
    // ��������� �� �������� (�������� ��� ��������), ����������� �� ������
    Entity* entity;

public:
    // ����������� ��� ������������� ������� Plot
    // ���������:
    //    texture_filename - ��� ����� �������� ������
    //    pos_x - X-���������� �������
    //    pos_y - Y-���������� �������
    Plot(std::string texture_filename, float pos_x, float pos_y);

    // ���������� �������� �� ������
    // ���������:
    //    _entity - ��������� �� �������� ��������
    // ����������: true, ���� �������� ������� ���������, ����� false
    bool placeEntity(Entity* _entity);

    // �������� ������ (������� ��������)
    // ����������: true, ���� ������ ������� �������, ����� false
    bool clear();

    // ������� ������ � ������ � �������� ��� � ���������
    // ���������:
    //    inventory - ��������� �� ��������� ������
    // ����������: true, ���� ������ ������� ������ � ��������, ����� false
    bool harvest(Inventory* inventory);

    // ���������, ����� �� ������ (��� ����������� ��������)
    // ����������: true, ���� ������ �����, ����� false
    bool isEmpty();

    // ���������, ������� �� �������� �� ������
    // ����������: true, ���� �������� �������, ����� false
    bool checkDeath();

    // ������ �������� �� ������
    void water();

    // �������� �������� �� ������
    void fertilise(Inventory* Inventory);

    // ��������� �������� �� ������
    void feed(Inventory* Inventory);

    // �������� ����, �����������, ��������� �� �������� �� ������
    // ����������: true, ���� �� ������ ��������, ����� false
    bool get_isPlant();

    // �������� ����, �����������, ��������� �� �������� �� ������
    // ����������: true, ���� �� ������ ��������, ����� false
    bool get_isAnimal();

    // �������� ������ ������ � ����������� �� ���� ��������
    // ����������: true, ���� ������ ������� �������, ����� false
    bool updateSprite();

    // ������������ ���� �������� �� ������
    // ����������: true, ���� �������� �������, ����� false
    bool growEntity();

    // �������� ������ (�������� �������� � ������������ ������)
    void plotReset();

    // ������� ��� ����� ��������
    void Slaughter(Inventory* Inventory);
};

#endif