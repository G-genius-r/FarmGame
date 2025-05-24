#include "../headers/Barley.h"
#include <iostream>

#define BARLEYWATER 4

// ������� ��� ��������� ���� �������� (������������ �� ������ Plant)
int Barley::get_type()
{
    return 2; // ���������� ��� ��� ������
}

// ����������� ������ Barley
Barley::Barley()
{
    growthStage = 0;      // ������������� ������ ����� ��������� 0
    wateringLevel = 0;    // ������������� ������ ������ ��������� 0
    isFertilised = false; // ������������� ��������� ��������� ��������� false
    

    // ������������� �������� ������� ��� ������ ������ ����� � ������� ������
    textureFilenames.push_back("sprites/barleySprite/barley0.png");
    textureFilenames.push_back("sprites/barleySprite/barley1.png");
    textureFilenames.push_back("sprites/barleySprite/barley2.png");
    textureFilenames.push_back("sprites/barleySprite/barley3.png");
    textureFilenames.push_back("sprites/barleySprite/barley0watered.png");
    textureFilenames.push_back("sprites/barleySprite/barley1watered.png");
    textureFilenames.push_back("sprites/barleySprite/barley2watered.png");
    textureFilenames.push_back("sprites/barleySprite/barley3watered.png");

    std::cout << "�������� ������ �������." << std::endl; // ����� ��������� � ��������
}

// ������� ��� ��������� ����� ������
bool Barley::grow()
{
    /* ������� ��� ����� */
    if (growthStage < 3 && wateringLevel == BARLEYWATER && isFertilised)
    {
        growthStage++;
        wateringLevel--;
        std::cout << "�������� ������ ������� �� ��������� ������!" << std::endl;
        return true; // ���������� true ��� �������� �����
    }
    else if (growthStage == 3)
        std::cout << "�������� ������ �������� ������������ ������ �����!" << std::endl;

    return false; // ���������� false, ���� ������� ����� �� ���������
}

// ������� ��� ��������� ������ ������
void Barley::water()
{
    if (wateringLevel < BARLEYWATER)
    {
        wateringLevel++;
        showWaterLevel();
    }
    // � ����� ������ ���������� ������� ����� ��� ���������
    waterLevelToDisplay = wateringLevel;
    waterDisplayClock.restart();
}

void Barley::showWaterLevel() {
    waterLevelToDisplay = wateringLevel;
    waterDisplayClock.restart();
}

void Barley::drawWaterLevel(sf::RenderWindow& window, float x, float y) {
    if (waterLevelToDisplay != -1 && waterDisplayClock.getElapsedTime().asSeconds() < 1.0f) {
        static sf::Font font;
        static bool fontLoaded = false;
        if (!fontLoaded) {
            font.loadFromFile("Silkscreen/CyrilicOld.ttf");
            fontLoaded = true;
        }
        sf::Text txt("�����: " + std::to_string(wateringLevel), font, 20);
        txt.setFillColor(sf::Color::Blue);
        txt.setPosition(x, y - 25);
        window.draw(txt);
    }
    else if (waterLevelToDisplay != -1) {
        waterLevelToDisplay = -1;
    }
}
