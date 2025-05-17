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
}

// Функция кормления животного зерном
bool Animal::eatGrain(Inventory* Inventory)
{
    if (hungryStatus >= 3)
    {
        std::cout << "Животное уже сыто" << std::endl;
        // Вывод сообщения пользователю, что животное не было накормлено
        Inventory->animalFeedAdd(1); // Добавление корма в инвентарь
        return false;                // Возврат false, так как животное уже сыто
    }
    else
    {
        set_hungryStatus(get_hungryStatus() + 1); // Увеличение статуса голода
        std::cout << "Животное накормлено, до полного насыщения нужно "
            << 3 - (get_hungryStatus()) << " порций корма" << std::endl;
        return true; // Возврат true после кормления животного
    }
}

// Функция проверки смерти животного
bool Animal::checkDeath()
{
    if (this->get_growthStage() >= this->get_lifespan() ||
        this->get_hungryStatus() == 0 ||
        this->get_isWatered() == 0)
    {
        isAnimal = false; // Установка флага животного в false при смерти
        std::cout << "Животное умерло." << std::endl;
        return true; // Возврат true, если животное умерло
    }
    else
    {
        return false; // Возврат false, если животное живо
    }
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