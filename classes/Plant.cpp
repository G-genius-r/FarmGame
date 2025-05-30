#include "../headers/Plant.h"

// ����������� ������ Plant
Plant::Plant() {
    growthStage = 0; // ������ �����  
    wateringLevel = 0; // ������� ������
    isFertilised = false; // ������������� ������� ��������� ��� false  
    isPlant = true; // ��������� �����, ��� ��� ��������  
    isAnimal = false; // ��������� �����, ��� ��� �� ��������  
    notifPanel = nullptr; // ������������� ��������� �� ������ �����������
}

// ��������� ������ �����������
void Plant::setNotificationPanel(NotificationPanel* panel) {
    notifPanel = panel;
}

// ������� ��� ��������� ��������  
void Plant::fertilise(Inventory* Inventory) {
    if (isFertilised == true) {
        if (notifPanel) notifPanel->addMessage("�������� ��� ���� ��������.");
        Inventory->fertiliserAdd(1); // ���������� ��������� � ���������  
        return;
    }
    isFertilised = true; // �������, ��� �������� ��������  
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
        if (notifPanel) notifPanel->addMessage("� ���! �������� �������.");
        return true; // ������� true, ���� �������� �������  
    }
    else {
        return false; // ������� false, ���� �������� ��� ����  
    }
}

std::string Plant::getFertiliserSprite() const {
    if (!isFertilised)
        return "sprites/fertilizer.png";
    else
        return "";
}