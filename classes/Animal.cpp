#include "../headers/Animal.h"

// Конструктор класса Animal
Animal::Animal()
{
    growthStage = 0;   // Инициализация стадии роста значением 0
    type = "";         // Инициализация типа пустой строкой
    hungryStatus = 0;  // Инициализация статуса голода значением 0
    wateringLevel = 0; // Инициализация уровня полива значением 0
    isAnimal = true;   // Установка флага животного в true
    isPlant = false;   // Установка флага растения в false
    notifPanel = nullptr;
}

// Функция кормления животного зерном
bool Animal::eatGrain(Inventory* Inventory) {
    if (hungryStatus >= 3) {
        if (notifPanel) notifPanel->addMessage("Животное уже сыто");
        Inventory->animalFeedAdd(1);
        return false;
    }
    else {
        set_hungryStatus(get_hungryStatus() + 1);
        if (notifPanel) {
            notifPanel->addMessage("до полного насыщения нужно " +
                std::to_string(4 - get_hungryStatus()) + " корма");
        }
        return true;
    }
}

// Функция проверки смерти животного
bool Animal::checkDeath() {
    if (this->get_growthStage() >= this->get_lifespan() ||
        this->get_hungryStatus() == 0 ||
        this->get_isWatered() == 0)
    {
        isAnimal = false;
        if (notifPanel) notifPanel->addMessage("Животное умерло");
        return true;
    }
    return false;
}

// Деструктор класса Animal
Animal::~Animal()
{
}

// Функция получения продолжительности жизни животного
int Animal::get_lifespan()
{
    return lifespan; // Возврат продолжительности жизни животного
}

// Установка панели уведомлений
void Animal::setNotificationPanel(NotificationPanel* panel)
{
    notifPanel = panel;
}

// Функция установки продолжительности жизни животного
void Animal::set_lifespan(int _lifespan)
{
    lifespan = _lifespan; // Установка продолжительности жизни животного
}

// Функция получения статуса голода животного
int Animal::get_hungryStatus()
{
    return hungryStatus; // Возврат статуса голода животного
}

// Функция установки статуса голода животного
void Animal::set_hungryStatus(int _hungryStatus)
{
    hungryStatus = _hungryStatus; // Установка статуса голода животного
}

std::string Animal::getHungerSprite() const {
    if (this->get_isAnimal()) {
        return textureFilenames[hungryStatus]; // Используем уровень голода для выбора текстуры
    }
    return "";
}
