#include "../headers/Plot.h"
#include <iostream>

// Конструктор класса Plot
Plot::Plot(std::string texture_filename, float pos_x, float pos_y) : GameTile(texture_filename, pos_x, pos_y) {
    entity = nullptr; // Инициализация указателя на сущность как nullptr
}

// Проверка, содержит ли участок растение
bool Plot::get_isPlant() {
    if (entity)
        return entity->get_isPlant();
    else
        return false;
}

// Проверка, содержит ли участок животное
bool Plot::get_isAnimal() {
    if (entity)
        return entity->get_isAnimal();
    else
        return false;
}

// Размещение сущности (растения или животного) на участке
bool Plot::placeEntity(Entity* _entity) {
    if (this->isEmpty() == false) {
        std::cout << "Сущность не размещена, так как участок занят" << std::endl;
        return false;
    }
    setUpBackSprite("sprites/Transparent.png", 16, 0);
    setUpFrontSprite(_entity->textureFilenames[0]);
    this->entity = _entity;
    std::cout << "Сущность успешно размещена на пустом участке" << std::endl;
    return true;
}

// Очистка участка (удаление сущности и сброс флагов)
bool Plot::clear() {
    delete entity;
    entity->set_isAnimal(false);
    entity->set_isPlant(false);
    return true;
}

// Полив сущности на участке
void Plot::water() {
    this->entity->water();
    if (this->entity->get_isPlant() == true && entity->get_isWatered() == entity->get_maxWateringLevel() && entity->get_growthStage() != 3) {
        setUpFrontSprite(entity->textureFilenames[entity->get_growthStage() + 4]);
    }
}

// Удобрение сущности на участке
void Plot::fertilise(Inventory* Inventory) {
    this->entity->fertilise(Inventory);
}

// Кормление сущности на участке
void Plot::feed(Inventory* Inventory) {
    this->entity->eatGrain(Inventory);
}

// Сбор урожая с участка и добавление в инвентарь
bool Plot::harvest(Inventory* inventory) {
    if (isEmpty() == false) {
        // Проверка типа сущности и сбор в зависимости от типа
        switch (entity->get_type())
        {
        case 1:
            if (entity->get_growthStage() == 3) {
                inventory->wheatGrainAdd(1); // Добавление пшеницы в инвентарь и уничтожение растения
                std::cout << "Пшеница собрана и добавлена в инвентарь!" << std::endl;
            }
            plotReset();
            return 1;
            break;
        case 2:
            if (entity->get_growthStage() == 3) {
                inventory->barleyGrainAdd(1); // Добавление ячменя в инвентарь и уничтожение растения
                std::cout << "Ячмень собран и добавлен в инвентарь" << std::endl;
            }
            plotReset();
            return 1;
            break;
        case 3:
            if (entity->getEggs() > 0) {
                std::cout << entity->getEggs() << " яиц добавлено в инвентарь" << std::endl;
                inventory->eggsAdd(entity->getEggs());
                entity->setEggs(0);
                std::cout << "Яйца собраны и добавлены в инвентарь" << std::endl;
                // Добавление накопленных яиц в инвентарь
            }
            return 1;
            break;
        case 4:
            if (entity->getWool() > 0) {
                std::cout << "1 шерсть добавлена в инвентарь" << std::endl;
                inventory->woolAdd(entity->getWool());
                entity->setWool(0);
                setUpFrontSprite("./sprites/sheepSprite/sheepShornSprite.png");
                std::cout << "Овца подстрижена, шерсть добавлена в инвентарь" << std::endl;
                // Добавление накопленной шерсти в инвентарь
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

// Забой животного на участке и добавление мяса в инвентарь
void Plot::Slaughter(Inventory* Inventory) {
    if (entity->get_isPlant() == true) {
        std::cout << "Ошибка: попытка забоя неживотной сущности" << std::endl;
    }
    else if (entity->get_type() == 3) {
        Inventory->meatAdd(1);
        plotReset();
        std::cout << "Курица забита" << std::endl;
    }
    else if (entity->get_type() == 4) {
        Inventory->meatAdd(3);
        plotReset();
        std::cout << "Овца забита" << std::endl;
    }
}

// Сброс участка путем удаления сущности и сброса флагов
void Plot::plotReset() {
    if (entity)
        delete entity;
    entity = nullptr;
    setUpFrontSprite("sprites/Transparent.png");
}

// Проверка, пуст ли участок
bool Plot::isEmpty() {
    if (entity == nullptr) {
        return true;
    }
    else {
        return false;
    }
}

// Рост сущности на участке
bool Plot::growEntity() {
    if (entity->grow()) {
        return true;
    }
    else
        return false;
}

// Проверка, погибла ли сущность на участке, и сброс при необходимости
bool Plot::checkDeath() {
    if (entity && entity->checkDeath() == 1) {
        plotReset();
        return 1;
    }
    return 0;
}

// Обновление спрайта сущности на участке
bool Plot::updateSprite() {
    if (this->isEmpty() == false)
    {
        std::string newFilename = entity->getCorrectFilename();
        setUpFrontSprite(newFilename);
        return 1;
    }
    return 0;
}