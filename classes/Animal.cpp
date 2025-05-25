#include "../headers/Animal.h"

// ����������� ������ Animal
Animal::Animal()
{
    growthStage = 0;   // ������������� ������ ����� ��������� 0
    type = "";         // ������������� ���� ������ �������
    hungryStatus = 0;  // ������������� ������� ������ ��������� 0
    wateringLevel = 0; // ������������� ������ ������ ��������� 0
    isAnimal = true;   // ��������� ����� ��������� � true
    isPlant = false;   // ��������� ����� �������� � false
    notifPanel = nullptr;
}

// ������� ��������� ��������� ������
bool Animal::eatGrain(Inventory* Inventory) {
    if (hungryStatus >= 3) {
        if (notifPanel) notifPanel->addMessage("�������� ��� ����");
        Inventory->animalFeedAdd(1);
        return false;
    }
    else {
        set_hungryStatus(get_hungryStatus() + 1);
        if (notifPanel) {
            notifPanel->addMessage("�� ������� ��������� ����� " +
                std::to_string(4 - get_hungryStatus()) + " �����");
        }
        return true;
    }
}

// ������� �������� ������ ���������
bool Animal::checkDeath() {
    if (this->get_growthStage() >= this->get_lifespan() ||
        this->get_hungryStatus() == 0 ||
        this->get_isWatered() == 0)
    {
        isAnimal = false;
        if (notifPanel) notifPanel->addMessage("�������� ������");
        return true;
    }
    return false;
}

// ���������� ������ Animal
Animal::~Animal()
{
}

// ������� ��������� ����������������� ����� ���������
int Animal::get_lifespan()
{
    return lifespan; // ������� ����������������� ����� ���������
}

// ��������� ������ �����������
void Animal::setNotificationPanel(NotificationPanel* panel)
{
    notifPanel = panel;
}

// ������� ��������� ����������������� ����� ���������
void Animal::set_lifespan(int _lifespan)
{
    lifespan = _lifespan; // ��������� ����������������� ����� ���������
}

// ������� ��������� ������� ������ ���������
int Animal::get_hungryStatus()
{
    return hungryStatus; // ������� ������� ������ ���������
}

// ������� ��������� ������� ������ ���������
void Animal::set_hungryStatus(int _hungryStatus)
{
    hungryStatus = _hungryStatus; // ��������� ������� ������ ���������
}

std::string Animal::getHungerSprite() const {
    if (this->get_isAnimal()) {
        return textureFilenames[hungryStatus]; // ���������� ������� ������ ��� ������ ��������
    }
    return "";
}
