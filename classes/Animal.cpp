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
}

// ������� ��������� ��������� ������
bool Animal::eatGrain(Inventory* Inventory)
{
    if (hungryStatus >= 3)
    {
        std::cout << "�������� ��� ����" << std::endl;
        // ����� ��������� ������������, ��� �������� �� ���� ����������
        Inventory->animalFeedAdd(1); // ���������� ����� � ���������
        return false;                // ������� false, ��� ��� �������� ��� ����
    }
    else
    {
        set_hungryStatus(get_hungryStatus() + 1); // ���������� ������� ������
        std::cout << "�������� ����������, �� ������� ��������� ����� "
            << 3 - (get_hungryStatus()) << " ������ �����" << std::endl;
        return true; // ������� true ����� ��������� ���������
    }
}

// ������� �������� ������ ���������
bool Animal::checkDeath()
{
    if (this->get_growthStage() >= this->get_lifespan() ||
        this->get_hungryStatus() == 0 ||
        this->get_isWatered() == 0)
    {
        isAnimal = false; // ��������� ����� ��������� � false ��� ������
        std::cout << "�������� ������." << std::endl;
        return true; // ������� true, ���� �������� ������
    }
    else
    {
        return false; // ������� false, ���� �������� ����
    }
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