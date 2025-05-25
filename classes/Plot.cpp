#include "../headers/Plot.h"
#include <iostream>

// Конструктор класса Plot
Plot::Plot(std::string texture_filename, float pos_x, float pos_y)
    : GameTile(texture_filename, pos_x, pos_y) {
    entity = nullptr;
    notifPanel = nullptr;
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
        if (notifPanel) notifPanel->addMessage("Сущность не размещена, участок занят");
        return false;
    }
    setUpBackSprite("sprites/Transparent.png", 16, 0);
    setUpFrontSprite(_entity->textureFilenames[0]);
    this->entity = _entity;

    // Передаем панель уведомлений новой сущности
    if (Plant* plant = dynamic_cast<Plant*>(_entity)) {
        plant->setNotificationPanel(notifPanel);
    }
    if (Animal* animal = dynamic_cast<Animal*>(_entity)) {
        animal->setNotificationPanel(notifPanel);
    }
}

// Очистка участка (удаление сущности и сброс флагов)
bool Plot::clear() {
    delete entity;
    entity->set_isAnimal(false);
    entity->set_isPlant(false);
    return true;
}

void Plot::setNotificationPanel(NotificationPanel* panel) {
    notifPanel = panel;
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
                if (notifPanel) notifPanel->addMessage("Пшеница собрана и добавлена в инвентарь!");
            }
            plotReset();
            return 1;
            break;
        case 2:
            if (entity->get_growthStage() == 3) {
                inventory->barleyGrainAdd(1); // Добавление ячменя в инвентарь и уничтожение растения
                if (notifPanel) notifPanel->addMessage("Ячмень собран и добавлен в инвентарь");
            }
            plotReset();
            return 1;
            break;
        case 3:
            if (entity->getEggs() > 0) {
                if (notifPanel) notifPanel->addMessage(std::to_string(entity->getEggs()) + " яиц добавлено в инвентарь");
                inventory->eggsAdd(entity->getEggs());
                entity->setEggs(0);
            }
            return 1;
            break;
        case 4:
            if (entity->getWool() > 0) {
                if (notifPanel) notifPanel->addMessage("1 шерсть добавлена в инвентарь");
                inventory->woolAdd(entity->getWool());
                entity->setWool(0);
                setUpFrontSprite("./sprites/sheepSprite/sheepShornSprite.png");
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
        if (notifPanel) notifPanel->addMessage("Ошибка: попытка забоя неживотной сущности");
    }
    else if (entity->get_type() == 3) {
        Inventory->meatAdd(1);
        plotReset();
        if (notifPanel) notifPanel->addMessage("Курица забита");
    }
    else if (entity->get_type() == 4) {
        Inventory->meatAdd(3);
        plotReset();
        if (notifPanel) notifPanel->addMessage("Овца забита");
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

std::string Plot::getFertiliserSpriteOnPlot() const {
    if (entity && entity->get_isPlant()) {
        Plant* plant = dynamic_cast<Plant*>(entity);
        if (plant) {
            return plant->getFertiliserSprite();
        }
    }
    return "";
}