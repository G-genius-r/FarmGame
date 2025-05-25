#include "../headers/Chicken.h"
#include <iostream>

// ����������� ������ Chicken
Chicken::Chicken() {
    eggs = 0; // ������������� ���������� ��� ��������� 0
    growthStage = 0; // ������������� ������ ����� ��������� 0
    lifespan = 10; // ��������� ����������������� ����� ������
    for (int i = 0; i < 11; i++) {
        textureFilenames.push_back("sprites/chickenSprite/chickenSprite1.png"); // ���������� ���� ������ �������� ������
    }
    isAnimal = true; // ��������� isAnimal � true
    isPlant = false; // ��������� isPlant � false
    hungryStatus = 0; // ������������� ������ ������ ��������� 0
    wateringLevel = 0; // ������������� ������ ������ ��������� 0
    waterLevelToDisplay = -1; // ������������� ���������� ������ ����
}

// ������� ��� ��������� ���� ��������� (������������ �� ������ Animal)
int Chicken::get_type() {
    return 3; // ���������� ��� ��� ������
}

// ������� ��� ��������� ������������ ��� �������
bool Chicken::layEgg() {
    if (eggs >= 3) {
        return false; // ���������� false, ���� ���������� ������������ ���������� ���
    }
    else {
        eggs++; // ����������� ���������� ���
        return true; // ���������� true ����� ������������ ����
    }
}

// ������� ��� ��������� ���������� ��� � ������
int Chicken::getEggs() {
    return eggs; // ���������� ���������� ���
}

// ������� ��� ��������� ���������� ��� ��� ������
void Chicken::setEggs(int _eggs) {
    eggs = _eggs; // ������������� ���������� ���
}

// ������� ��� ��������� ����� ������
bool Chicken::grow() {
    // ��� �������� ������� grow �� ������ ������

    // �������� ������� ��� ������������ ���
    if (wateringLevel == 3 && hungryStatus == 3) {
        layEgg();
        if (notifPanel) notifPanel->addMessage("������ �������� ����");
    }

    wateringLevel--; // ��������� ������� ������
    if (wateringLevel < 0) wateringLevel = 0;

    hungryStatus--; // ��������� ������� ������
    if (hungryStatus < 0) hungryStatus = 0;

    growthStage++; // ����������� ������ �����
    if (notifPanel) notifPanel->addMessage("������ ������� �� ��������: " + std::to_string(growthStage));
    return true; // ���������� true ��� ������������� �����
}

// ������� ��� ��������� ������ ������
void Chicken::water() {
    if (wateringLevel < 3) {
        wateringLevel++; // ����������� ������� ������
        showWaterLevel();
    }
    // � ����� ������ ���������� ������� ����� ��� �������
    waterLevelToDisplay = wateringLevel;
    waterDisplayClock.restart();
}

void Chicken::showWaterLevel() {
    waterLevelToDisplay = wateringLevel;
    waterDisplayClock.restart();
}

void Chicken::drawWaterLevel(sf::RenderWindow& window, float x, float y) {
    if (waterLevelToDisplay != -1 && waterDisplayClock.getElapsedTime().asSeconds() < 1.0f) {
        static sf::Font font;
        static bool fontLoaded = false;
        if (!fontLoaded) {
            font.loadFromFile("Silkscreen/CyrilicOld.ttf");
            fontLoaded = true;
        }
        sf::Text txt("����: " + std::to_string(wateringLevel), font, 20);
        txt.setFillColor(sf::Color::Blue);
        txt.setPosition(x, y - 25);
        window.draw(txt);
    }
    else if (waterLevelToDisplay != -1) {
        waterLevelToDisplay = -1;
    }
}