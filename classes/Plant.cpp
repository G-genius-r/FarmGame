#include "../headers/Plant.h"

// ����������� ������ Plant
Plant::Plant() {
    growthStage = 0; // ������ �����  
    wateringLevel = 0; // ������� ������
    isFertilised = false; // ������������� ������� ��������� ��� false  
    isPlant = true; // ��������� �����, ��� ��� ��������  
    isAnimal = false; // ��������� �����, ��� ��� �� ��������  
}

// ������� ��� ��������� ��������  
void Plant::fertilise(Inventory* Inventory) {
    if (isFertilised == true) {
        std::cout << "�������� ��� ���� ��������." << std::endl;
        Inventory->fertiliserAdd(1); // ���������� ��������� � ���������  
        return;
    }
    isFertilised = true; // �������, ��� �������� ��������  
    std::cout << "�������� ���� ��������." << std::endl;
}

// ������� ��� ��������� ����� ��������  
bool Plant::grow() {
    if (wateringLevel == 5 && isFertilised) {
        growthStage++; // ���������� ������ �����  
        wateringLevel--; // ���������� ������ ������  
        return true; // ������� true, ���� ���� �������  
    }
    wateringLevel--; // ���������� ������ ������  
    return false; // ������� false, ���� ������� ��� ����� �� ���������  
}

// ������� ��� ��������, ������� �� �������� ��-�� ���������� ����  
bool Plant::checkDeath() {
    if (this->get_isWatered() == 0) {
        std::cout << "� ���! �������� �������." << std::endl;
        return true; // ������� true, ���� �������� �������  
    }
    else {
        return false; // ������� false, ���� �������� ��� ����  
    }
}

std::string Plant::getFertiliserSprite() const {
    if (!isFertilised)
        return "sprites/inventorySprite/fertiliserSprite.png";
    else
        return "";
}