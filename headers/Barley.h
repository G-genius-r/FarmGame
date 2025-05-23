#ifndef BARLEY_H
#define BARLEY_H
#include "Plant.h"

// ����� Barley, �������������� ������ � ���� (����������� �� Plant)
class Barley : public Plant
{
private:

    int waterLevelToDisplay = -1;
    sf::Clock waterDisplayClock;

public:
    void showWaterLevel();
    void drawWaterLevel(sf::RenderWindow& window, float x, float y);
    // ����������� ��� ������������� ������� Barley
    Barley();

    // ���������� ����������� ������� ��� ��������� ���� ��������
    // ����������: ��� �������� (� ������ ������ 2 ��� ������)
    int get_type();


    // ���������� ����������� ������� ��� ��������� ����� ��������
    // ����������: true, ���� �������� �������, ����� false
    bool grow();

    // ���������� ����������� ������� ��� ������ ��������
    void water();

    void draw(sf::RenderWindow& window, float x, float y);

    // ��������� ������������� ������ ������ ��� ������
    // ����������: ������������ ������� ������ (��� ������ - 4)
    int get_maxWateringLevel() { return(4); };
};

#endif