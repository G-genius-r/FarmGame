#pragma once
#ifndef GAMETILE_H
#define GAMETILE_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>

/*�����/���� ��������� �� ����� 10x10. ������ ������ ������������ �������� GameTile.
GameTile - ��� ������� ����������� �������, �� ������� �������� �� ���������, ���� �� ������ ��� ������ �������.*/
class GameTile
{
protected:
    // �������� � ������ ��� ����� ���������, ��������� � �������
    sf::Texture selectionBoxTexture;
    sf::Sprite selectionBoxSprite;

    // ������� ������
    sf::Vector2f pos;

    // �������� � ������ ��� ���� ������
    sf::Texture backTexture;
    sf::Sprite backSprite;

    // �������� � ������ ��� ��������� ����� ������
    sf::Texture frontTexture;
    sf::Sprite frontSprite;

public:
    // ����������� �� ��������� ��� ������������� ������� GameTile
    GameTile();

    // ����������� ��� ������������� ������� GameTile � ��������� ��������� ���� � ��������
    // ������� ���������: backTextureFilename - ��� ����� �������� ����.
    //                   pos_x - X-���������� �������.
    //                   pos_y - Y-���������� �������.
    GameTile(std::string backTextureFilename, float pos_x, float pos_y);

    // ��������� ������� ���� ������ � �������������� ���������� ����� ��������
    // ������� ���������: backTextureFilename - ��� ����� �������� ����.
    // ������������ ��������: true, ���� ������ ���� ������� ��������, ����� false.
    bool setUpBackSprite(std::string backTextureFilename);

    // ��������� ������� ���� ������ � �������������� ���������� ����� �������� � �������
    // ������� ���������: backTextureFilename - ��� ����� �������� ����.
    //                   pos_x - X-���������� �������.
    //                   pos_y - Y-���������� �������.
    // ������������ ��������: true, ���� ������ ���� ������� ��������, ����� false.
    bool setUpBackSprite(std::string backTextureFilename, int pos_x, int pos_y);

    // ��������� ������� ��������� ����� ������ � �������������� ���������� ����� ��������
    // ������� ���������: frontTextureFilename - ��� ����� �������� ��������� �����.
    // ������������ ��������: true, ���� ������ ��������� ����� ������� ��������, ����� false.
    bool setUpFrontSprite(std::string frontTextureFilename);

    // ��������� ������� ��������� ����� ������ � �������������� ���������� ����� �������� � �������
    // ������� ���������: frontTextureFilename - ��� ����� �������� ��������� �����.
    //                    pos_x - X-���������� �������.
    //                    pos_y - Y-���������� �������.
    // ������������ ��������: true, ���� ������ ��������� ����� ������� ��������, ����� false.
    bool setUpFrontSprite(std::string frontTextureFilename, float cellWidth, float cellHeight);

    // ��������� ����� ��������� �� ������ � �������������� ���������������� ����
    // ������� ���������: window - ��������� �� ���� ���������� SFML.
    void drawSelectionBox(sf::RenderWindow* window);

    // ��������� ������� ������
    // ������� ���������: pos_x - X-���������� ����� �������.
    //                    pos_y - Y-���������� ����� �������.
    void set_pos(float pos_x, float pos_y);

    void setScale(float width, float height);

    // ��������� ������� ������
    // ������������ ��������: ������� ������ � ���� 2D �������.
    sf::Vector2f get_pos();

    // ������ ��� �������� ���� ������
    // ������������ ��������: �������� ���� ������.
    sf::Texture get_backTexture() { return backTexture; };

    // ������ ��� ������� ���� ������
    // ������������ ��������: ������ ���� ������.
    sf::Sprite get_backSprite() { return backSprite; };

    // ������ ��� �������� ��������� ����� ������
    // ������������ ��������: �������� ��������� ����� ������.
    sf::Texture get_frontTexture() { return frontTexture; };

    // ������ ��� ������� ��������� ����� ������
    // ������������ ��������: ������ ��������� ����� ������.
    sf::Sprite get_frontSprite() { return frontSprite; };
};
#endif