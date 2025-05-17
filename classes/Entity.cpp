#include "../headers/Entity.h"

// ����������� ������ Entity
Entity::Entity() {
    // ����������� �� ���������, �� ������� ����������� �������������
}

// ��������� ������� ������ ����� ��������
int Entity::get_growthStage() {
    return growthStage; // ���������� ������ �����
}

// ��������� ������ ������ ��������
int Entity::get_isWatered() {
    return wateringLevel; // ���������� ������� ������
}

// ��������� ������ ����� ��������
void Entity::set_growthStage(int _growthStage) {
    growthStage = _growthStage; // ������������� ������ �����
}

// ��������� ������ ������ ��������
void Entity::set_isWatered(int _wateringLevel) {
    wateringLevel = _wateringLevel; // ������������� ������� ������
}

// ��������� ���������� ��� (�� ��� ���� ���������)
int Entity::getEggs() {
    std::cout << "������ �������� ���� - �������� �� �������� �������" << std::endl;
    return 0; // ���������� 0, ��� ��� ��� �� ������
}

// �������� ������� ������ (�� ��� ���� ���������)
bool Entity::getWool() {
    std::cout << "������ �������� ������ - �������� �� �������� �����" << std::endl;
    return 0; // ���������� false, ��� ��� ��� �� ����
}

// ��������� ���������� ��� (�� ��� ���� ���������)
void Entity::setEggs(int _Eggs) {
    _Eggs = isPlant; // ������������ ������������ (��������, ������ ���� isPlant = _Eggs)
    isPlant = _Eggs;
    std::cout << "������ ���������� ���� - �������� �� �������� �������" << std::endl;
}

// ��������� ������� ������ (�� ��� ���� ���������)
void Entity::setWool(bool _Wool) {
    _Wool = isPlant; // ������������ ������������ (��������, ������ ���� isPlant = _Wool)
    isPlant = _Wool;
    std::cout << "������ ���������� ������ - �������� �� �������� �����" << std::endl;
}

// ��������� ����� "�������� ���������"
void Entity::set_isPlant(bool _isPlant) {
    isPlant = _isPlant; // ������������� ���� ��������
}

// ��������� ����� "�������� ��������"
void Entity::set_isAnimal(bool _isAnimal) {
    isAnimal = _isAnimal; // ������������� ���� ���������
}

// ��������, �������� �� �������� ���������
bool Entity::get_isPlant() {
    return isPlant; // ���������� ���� ��������
}

// ��������, �������� �� �������� ��������
bool Entity::get_isAnimal() {
    return isAnimal; // ���������� ���� ���������
}

// ��������� �������� ����� (�� ��� ���� ���������)
bool Entity::eatGrain(Inventory*) {
    return false; // ���������� false, ��� ��� �������� ����� �� ���������
}

// ��������� ����������� ����� ����� �������� ��� ��������
std::string Entity::getCorrectFilename()
{
    if (this->get_type() == 4) { // ���� ��� ���� (����������� ������)
        if (this->getWool() == true) // ���� ���� ������
            return(textureFilenames[1]); // ���������� �������� � �������
        else
            return(textureFilenames[0]); // ���������� ������� ��������
    }
    return(textureFilenames[growthStage]); // ���������� �������� � ����������� �� ������ �����
}

// ��������� ��������� (�� ��� ���� ���������)
void Entity::fertilise(Inventory* Inventory) {
    Inventory->eggsAdd(0); // ��������� ���� (������������ �������� �������, ������ ���� ������� � ������� ��� ����������)
}