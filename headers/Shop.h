#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "Inventory.h"
#ifndef SHOP_H
#define SHOP_H


/*������� - ��� �����, ��� ����� ����� �������� � ��������� ���� �������.
�������� � ���� ����������� �� ���� ��������� �����, ��� ���������
��������� ����� �������� ��������, ��������, ������.*/
class Shop
{
private:
    // �������� � ������ ���� ��������
    sf::Texture Backdrop_texture;
    sf::Sprite Backdrop_sprite;

    // ����, �����������, ������ �� �������
    bool shopIsOpen;

    // ������� ��������
    int shop_pos_x;
    int shop_pos_y;

public:
    // ����������� ��� ������������� ������� Shop
    Shop();

    // ������ ��� ����� �������� ��������
    // ����������: true, ���� ������� ������, ����� false
    bool get_shopIsOpen();

    // ����������� ������ �������� �� ����
    // ���������: window - ��������� �� ���� ���������� SFML.
    //            display_string - ����� ��� �����������.
    //            x - ���������� X ��� ���������������� ������.
    //            y - ���������� Y ��� ���������������� ������.
    void displayShopText(sf::RenderWindow* window, std::string display_string, int x, int y);

    // ������ ��� ����� �������� ��������
    // ���������: _shopIsOpen - ���������� ��������, �����������, ������ �� �������
    void set_shopIsOpen(bool _shopIsOpen);

    // ������� ������� � ��������� ������ ����������������� � ���
    // ���������: window - ��������� �� ���� ���������� SFML.
    //            money - ���������� ����� � ������
    // ����������: true, ���� ������� ������ � ����� ����������������, ����� false
    bool shopOpen(sf::RenderWindow* window, int money);

    // ������� ��� ������� ���� ������� � ���������
    bool sellGoods(Inventory* Inventory);
};


#endif