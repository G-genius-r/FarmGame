#include "../headers/Chicken.h"

// Конструктор класса Chicken
Chicken::Chicken() {
    eggs = 0; // Инициализация количества яиц значением 0
    growthStage = 0; // Инициализация стадии роста значением 0
    lifespan = 10; // Установка продолжительности жизни курицы
    for (int i = 0; i < 11; i++) {
        textureFilenames.push_back("sprites/chickenSprite/chickenSprite1.png"); // Добавление имен файлов спрайтов курицы
    }
    isAnimal = true; // Установка isAnimal в true
    isPlant = false; // Установка isPlant в false
    hungryStatus = 0; // Инициализация уровня голода значением 0
    wateringLevel = 0; // Инициализация уровня полива значением 0
}

// Функция для получения типа животного (унаследована от класса Animal)
int Chicken::get_type() {
    return 3; // Возвращает тип для курицы
}

// Функция для симуляции откладывания яиц курицей
bool Chicken::layEgg() {
    if (eggs >= 3) {
        return false; // Возвращает false, если достигнуто максимальное количество яиц
    }
    else {
        eggs++; // Увеличивает количество яиц
        return true; // Возвращает true после откладывания яйца
    }
}

// Функция для получения количества яиц у курицы
int Chicken::getEggs() {
    return eggs; // Возвращает количество яиц
}

// Функция для установки количества яиц для курицы
void Chicken::setEggs(int _eggs) {
    eggs = _eggs; // Устанавливает количество яиц
}

// Функция для симуляции роста курицы
bool Chicken::grow() {
    // Для животных функция grow не меняет спрайт

    // Проверка условий для откладывания яиц
    if (wateringLevel == 3 && hungryStatus == 3) {
        layEgg();
        std::cout << "Курица отложила яйцо" << std::endl;
    }

    wateringLevel--; // Уменьшает уровень полива
    if (wateringLevel < 0) wateringLevel = 0;

    hungryStatus--; // Уменьшает уровень голода
    if (hungryStatus < 0) hungryStatus = 0;

    growthStage++; // Увеличивает стадию роста
    std::cout << "Курица выросла до возраста: " << growthStage << std::endl;
    return true; // Возвращает true для подтверждения роста
}

// Функция для симуляции полива курицы
void Chicken::water() {
    if (wateringLevel < 3) {
        wateringLevel++; // Увеличивает уровень полива
        std::cout << "Уровень полива курицы: " << wateringLevel << std::endl;
        return;
    }
    else {
        std::cout << "Уровень полива = " << wateringLevel << " (курица уже полита)" << std::endl;
    }
}