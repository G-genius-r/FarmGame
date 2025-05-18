#include "../headers/Sheep.h"

// ����������� ������ Sheep
Sheep::Sheep() {
    wool = false; // ������������� ������� ������ ��� false
    growthStage = 0; // ������������� ������ ����� ��������� 0
    lifespan = 20; // ��������� ����������������� ����� ����
    textureFilenames.push_back("./sprites/sheepSprite/sheepShornSprite.png"); // �������� �������� ��������� ����
    textureFilenames.push_back("./sprites/sheepSprite/sheepSprite.png"); // �������� �������� ���� � �������
    isAnimal = true; // ��������� �����, ��� ��� ��������
    hungryStatus = 0; // ������������� ������� ������ ��������� 0
    wateringLevel = 0; // ������������� ������ ������ ��������� 0
}

// ������� �������� ������������ ������ �����
void Sheep::produceWool() {
    wool = true; // ��������� ������� ������ � true
}

// ������� �������� ������� ������ � ����
bool Sheep::getWool() {
    return wool;
}

// ������� ��������� ������� ������ � ����
void Sheep::setWool(bool _wool) {
    wool = _wool;
}

// ������� ��������� ���� �������� (����)
int Sheep::get_type() {
    return 4;
}

// ������� �������� ����� ����
bool Sheep::grow() {
    if (wateringLevel == 3 && hungryStatus == 3) {
        produceWool(); // �������� ������������ ������ ��� ������� ������ � ���������
        std::cout << "���� ������ � �������" << std::endl;
    }
    wateringLevel--;
    if (wateringLevel < 0) wateringLevel = 0;
    hungryStatus--;
    if (hungryStatus < 0) hungryStatus = 0;
    growthStage++;
    std::cout << "���� ������� �� ��������:" << growthStage << std::endl;
    return true;
}

// ������� ������ ����
void Sheep::water() {
    if (wateringLevel < 3) {
        wateringLevel++;
        std::cout << "���� ������� �� ������: " << wateringLevel << std::endl;
        return;
    }
    else {
        std::cout << "������� ������ =" << wateringLevel << " (���� ��� �������)" << std::endl;
    }
}