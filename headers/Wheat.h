#ifndef WHEAT_H
#define WHEAT_H
#include "Plant.h"

// ����� Wheat, �������������� ������� � ���� (����������� �� Plant)
class Wheat : public Plant
{
private:

    int waterLevelToDisplay = -1;
    sf::Clock waterDisplayClock;
    // � private-������:
    sf::Texture waterTexture;
    sf::Sprite waterSprite;

public:
    void showWaterLevel();
    void drawWaterLevel(sf::RenderWindow& window, float x, float y);
    // ����������� ��� ������������� ������� Wheat
    Wheat();

    // ���������� ����������� ������� ��� ��������� ���� ��������
    // ����������: ��� �������� (� ������ ������ 1 ��� �������)
    int get_type();

    // ���������� ����������� ������� ��� ��������� ����� ��������
    // ����������: true, ���� �������� �������, ����� false
    bool grow();

    // ���������� ����������� ������� ��� ������ ��������
    void water();

    void draw(sf::RenderWindow& window, float x, float y);

    // ��������� ������������� ������ ������ ��� �������
    // ����������: ������������ ������� ������ (��� ������� - 5)
    int get_maxWateringLevel() { return(5); };
};

#endif