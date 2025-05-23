#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>

/*����� Inventory ������ ��� ������� ����� � ����������,
��� ����� ����� ��������, � ��� ���. ���������
����� ��������� ��� ������ �� ����.*/
class Inventory
{
private:
    /*�������*/
    int money;          // ������
    int fertiliser;     // ���������
    int animalFeed;     // ���� ��� ��������

    /*������ ��� �������*/
    int wheatGrain;     // ����� �������
    int barleyGrain;   // ����� ������
    int wool;          // ������
    int eggs;          // ����
    int meat;          // ����

    /*������*/
    int wheatSeed;      // ������ �������
    int barleySeed;    // ������ ������

    /*��������*/
    int sheep;         // ����
    int chickens;      // ����

    /*����������� ��� ������ Inventory ��������*/
    sf::Texture backdrop_texture;  // �������� ���� ���������
    sf::Sprite  backdrop_sprite;   // ������ ���� ���������
    int inventoryPos_x;            // ������� ��������� �� X
    int inventoryPos_y;            // ������� ��������� �� Y

public:
    /*�����������*/
    Inventory();

    /*���������� � �������� �� �����*/
    bool saveDataToFile(const std::string& filename);    // ��������� ������ � ����
    bool loadDataFromFile(const std::string& filename);  // ��������� ������ �� �����

    /*������� ��� ������� � ��������� ��������� ������ ���������*/
    void moneyAdd(int amount);            // �������� ������
    bool moneyTake(int amount);           // ������� ������ (���� ��������)
    void fertiliserAdd(int amount);       // �������� ���������
    bool fertiliserTake(int amount);      // ������������ ��������� (���� ��������)
    void wheatGrainAdd(int amount);       // �������� ����� �������
    bool wheatGrainTake(int amount);      // ������������ ����� �������
    void barleyGrainAdd(int amount);      // �������� ����� ������
    bool barleyGrainTake(int amount);     // ������������ ����� ������
    void wheatSeedAdd(int amount);        // �������� ������ �������
    bool wheatSeedTake(int amount);       // ������������ ������ �������
    void barleySeedAdd(int amount);       // �������� ������ ������
    bool barleySeedTake(int amount);      // ������������ ������ ������
    void woolAdd(int amount);            // �������� ������
    bool woolTake(int amount);           // ������������ ������
    void eggsAdd(int amount);            // �������� ����
    bool eggsTake(int amount);          // ������������ ����
    void ChickenAdd(int amount);        // �������� ���
    bool ChickenTake(int amount);      // ������ ��� (�������/������)
    void SheepAdd(int amount);         // �������� ����
    bool SheepTake(int amount);       // ������ ���� (�������/������)
    void animalFeedAdd(int amount);    // �������� ���� ��� ��������
    bool animalFeedTake(int amount);   // ������������ ���� ��� ��������
    void meatAdd(int amount);         // �������� ����
    bool meatTake(int amount);        // ������������ ����

    // ������� ��� ������� � �����
    unsigned int getMoney();
    int getWool();
    int getEggs();
    int getWheatGrain();
    int getBarleyGrain();
    int getMeat();
    int getFertiliser() { return(fertiliser); };    // �������� ���������� ���������
    int getWheatSeed() { return(wheatSeed); };      // �������� ���������� ����� �������
    int getBarleySeed() { return(barleySeed); };    // �������� ���������� ����� ������
    int getSheep() { return(sheep); };             // �������� ���������� ����
    int getChickens() { return(chickens); };       // �������� ���������� ���

    /*������� ��� ����������� ���������*/
    bool show(sf::RenderWindow* window);                      // �������� ���������
    void displayInvText(sf::RenderWindow* window, std::string displayString, int x, int y); // ���������� ����� � ���������
};

#endif