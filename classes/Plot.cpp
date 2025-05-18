#include "../headers/Plot.h"
#include <iostream>

// ����������� ������ Plot
Plot::Plot(std::string texture_filename, float pos_x, float pos_y) : GameTile(texture_filename, pos_x, pos_y) {
    entity = nullptr; // ������������� ��������� �� �������� ��� nullptr
}

// ��������, �������� �� ������� ��������
bool Plot::get_isPlant() {
    if (entity)
        return entity->get_isPlant();
    else
        return false;
}

// ��������, �������� �� ������� ��������
bool Plot::get_isAnimal() {
    if (entity)
        return entity->get_isAnimal();
    else
        return false;
}

// ���������� �������� (�������� ��� ���������) �� �������
bool Plot::placeEntity(Entity* _entity) {
    if (this->isEmpty() == false) {
        std::cout << "�������� �� ���������, ��� ��� ������� �����" << std::endl;
        return false;
    }
    setUpBackSprite("sprites/Transparent.png", 16, 0);
    setUpFrontSprite(_entity->textureFilenames[0]);
    this->entity = _entity;
    std::cout << "�������� ������� ��������� �� ������ �������" << std::endl;
    return true;
}

// ������� ������� (�������� �������� � ����� ������)
bool Plot::clear() {
    delete entity;
    entity->set_isAnimal(false);
    entity->set_isPlant(false);
    return true;
}

// ����� �������� �� �������
void Plot::water() {
    this->entity->water();
    if (this->entity->get_isPlant() == true && entity->get_isWatered() == entity->get_maxWateringLevel() && entity->get_growthStage() != 3) {
        setUpFrontSprite(entity->textureFilenames[entity->get_growthStage() + 4]);
    }
}

// ��������� �������� �� �������
void Plot::fertilise(Inventory* Inventory) {
    this->entity->fertilise(Inventory);
}

// ��������� �������� �� �������
void Plot::feed(Inventory* Inventory) {
    this->entity->eatGrain(Inventory);
}

// ���� ������ � ������� � ���������� � ���������
bool Plot::harvest(Inventory* inventory) {
    if (isEmpty() == false) {
        // �������� ���� �������� � ���� � ����������� �� ����
        switch (entity->get_type())
        {
        case 1:
            if (entity->get_growthStage() == 3) {
                inventory->wheatGrainAdd(1); // ���������� ������� � ��������� � ����������� ��������
                std::cout << "������� ������� � ��������� � ���������!" << std::endl;
            }
            plotReset();
            return 1;
            break;
        case 2:
            if (entity->get_growthStage() == 3) {
                inventory->barleyGrainAdd(1); // ���������� ������ � ��������� � ����������� ��������
                std::cout << "������ ������ � �������� � ���������" << std::endl;
            }
            plotReset();
            return 1;
            break;
        case 3:
            if (entity->getEggs() > 0) {
                std::cout << entity->getEggs() << " ��� ��������� � ���������" << std::endl;
                inventory->eggsAdd(entity->getEggs());
                entity->setEggs(0);
                std::cout << "���� ������� � ��������� � ���������" << std::endl;
                // ���������� ����������� ��� � ���������
            }
            return 1;
            break;
        case 4:
            if (entity->getWool() > 0) {
                std::cout << "1 ������ ��������� � ���������" << std::endl;
                inventory->woolAdd(entity->getWool());
                entity->setWool(0);
                setUpFrontSprite("./sprites/sheepSprite/sheepShornSprite.png");
                std::cout << "���� �����������, ������ ��������� � ���������" << std::endl;
                // ���������� ����������� ������ � ���������
            }
            return 1;
            break;
        default:
            plotReset();
            return 0;
            break;
        }
    }
    return false;
}

// ����� ��������� �� ������� � ���������� ���� � ���������
void Plot::Slaughter(Inventory* Inventory) {
    if (entity->get_isPlant() == true) {
        std::cout << "������: ������� ����� ���������� ��������" << std::endl;
    }
    else if (entity->get_type() == 3) {
        Inventory->meatAdd(1);
        plotReset();
        std::cout << "������ ������" << std::endl;
    }
    else if (entity->get_type() == 4) {
        Inventory->meatAdd(3);
        plotReset();
        std::cout << "���� ������" << std::endl;
    }
}

// ����� ������� ����� �������� �������� � ������ ������
void Plot::plotReset() {
    if (entity)
        delete entity;
    entity = nullptr;
    setUpFrontSprite("sprites/Transparent.png");
}

// ��������, ���� �� �������
bool Plot::isEmpty() {
    if (entity == nullptr) {
        return true;
    }
    else {
        return false;
    }
}

// ���� �������� �� �������
bool Plot::growEntity() {
    if (entity->grow()) {
        return true;
    }
    else
        return false;
}

// ��������, ������� �� �������� �� �������, � ����� ��� �������������
bool Plot::checkDeath() {
    if (entity && entity->checkDeath() == 1) {
        plotReset();
        return 1;
    }
    return 0;
}

// ���������� ������� �������� �� �������
bool Plot::updateSprite() {
    if (this->isEmpty() == false)
    {
        std::string newFilename = entity->getCorrectFilename();
        setUpFrontSprite(newFilename);
        return 1;
    }
    return 0;
}