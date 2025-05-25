#pragma once
#ifndef CHICKEN_H
#define CHICKEN_H

#include "Animal.h"
#include <SFML/Graphics.hpp>

// ����� Chicken (������), ����������� �� Animal
class Chicken : public Animal
{
private:
    int eggs; // ���������� ��� � ������
    int waterLevelToDisplay; // ������� ������� ���� ��� �����������
    sf::Clock waterDisplayClock; // ������ ��� ����������� ������ ����

public:
    // ����������� ������ Chicken
    Chicken();

    // �������� ����
    // ����������: true ���� �������, false ���� ��������� �������� ���
    bool layEgg();

    // �������� ������� ���������� ���
    int getEggs();

    // ���������� ���������� ���
    // ��������: _eggs - ���������� ��� ��� ���������
    void setEggs(int _eggs);

    // �������� ��� �������� (��������������� ����������� �������)
    // ����������: ��� ������ (����������� ��������)
    int get_type() override;

    // ������������ ���� ������ (��������������� ����������� �������)
    // ����������: true ���� ���� ���������
    bool grow() override;

    // ������ ������ (��������������� ����������� �������)
    void water() override;

    // �������� ������� ����
    void showWaterLevel();

    // ���������� ������� ����
    // ���������:
    // window - ���� ��� ���������
    // x, y - ���������� ��� ���������
    void drawWaterLevel(sf::RenderWindow& window, float x, float y);

    // �������� ������������ ������� ������
    // ����������: 3 (������������ ������� ������ ��� ������)
    int get_maxWateringLevel() override { return 3; };

    // ���������� ������ Chicken
    ~Chicken() {};
};

#endif