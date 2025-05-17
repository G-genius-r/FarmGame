#include "../headers/Chicken.h"

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
        std::cout << "������ �������� ����" << std::endl;
    }

    wateringLevel--; // ��������� ������� ������
    if (wateringLevel < 0) wateringLevel = 0;

    hungryStatus--; // ��������� ������� ������
    if (hungryStatus < 0) hungryStatus = 0;

    growthStage++; // ����������� ������ �����
    std::cout << "������ ������� �� ��������: " << growthStage << std::endl;
    return true; // ���������� true ��� ������������� �����
}

// ������� ��� ��������� ������ ������
void Chicken::water() {
    if (wateringLevel < 3) {
        wateringLevel++; // ����������� ������� ������
        std::cout << "������� ������ ������: " << wateringLevel << std::endl;
        return;
    }
    else {
        std::cout << "������� ������ = " << wateringLevel << " (������ ��� ������)" << std::endl;
    }
}