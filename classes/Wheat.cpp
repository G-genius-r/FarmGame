#include "../headers/Wheat.h"
#include <iostream>

#define WHEATWATER 5

// ������� ��� ��������� ���� �������� (������������ �� ������ Plant)
int Wheat::get_type()
{
    return 1; // ���������� ��� ��� �������
}

// ����������� ������ Wheat
Wheat::Wheat()
{
    growthStage = 0;      // ������������� ������ ����� ��������� 0
    wateringLevel = 0;    // ������������� ������ ������ ��������� 0
    isFertilised = false; // ������������� ��������� ��������� ��������� false

    // ������������� �������� ������� ��� ������ ������ ����� � ������� ������
    textureFilenames.push_back("sprites/wheatSprite/wheat0.png");
    textureFilenames.push_back("sprites/wheatSprite/wheat1.png");
    textureFilenames.push_back("sprites/wheatSprite/wheat2.png");
    textureFilenames.push_back("sprites/wheatSprite/wheat3.png");
    textureFilenames.push_back("sprites/wheatSprite/wheat0watered.png");
    textureFilenames.push_back("sprites/wheatSprite/wheat1watered.png");
    textureFilenames.push_back("sprites/wheatSprite/wheat2watered.png");
    textureFilenames.push_back("sprites/wheatSprite/wheat3watered.png");

    std::cout << "�������� ������� �������." << std::endl; // ��������� � ��������
}

// ������� ��� ��������� ����� �������
bool Wheat::grow()
{
    /* ������� ��� ����� */
    if (growthStage < 3 && wateringLevel == WHEATWATER && isFertilised)
    {
        growthStage++;
        wateringLevel--;
        std::cout << "�������� ������� ������� �� ��������� ������!" << std::endl;
        return true; // ���������� true ��� �������� �����
    }
    else if (growthStage == 3)
        std::cout << "�������� ������� �������� ������������ ������ �����!" << std::endl;

    return false; // ���������� false, ���� ������� ����� �� ���������
}

// ������� ��� ��������� ������ �������
void Wheat::water()
{
    if (wateringLevel < WHEATWATER)
    {
        wateringLevel++;
        showWaterLevel();
    }
    // � ����� ������ ���������� ������� ����� ��� ���������
    waterLevelToDisplay = wateringLevel;
    waterDisplayClock.restart();
}

void Wheat::showWaterLevel() {
    waterLevelToDisplay = wateringLevel;
    waterDisplayClock.restart();
}

void Wheat::drawWaterLevel(sf::RenderWindow& window, float x, float y) {
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