#include "../headers/Sheep.h"

// Конструктор класса Sheep
Sheep::Sheep() {
    wool = false; // Инициализация наличия шерсти как false
    growthStage = 0; // Инициализация стадии роста значением 0
    lifespan = 20; // Установка продолжительности жизни овцы
    textureFilenames.push_back("./sprites/sheepSprite/sheepShornSprite.png"); // Загрузка текстуры стриженой овцы
    textureFilenames.push_back("./sprites/sheepSprite/sheepSprite.png"); // Загрузка текстуры овцы с шерстью
    isAnimal = true; // Установка флага, что это животное
    hungryStatus = 0; // Инициализация статуса голода значением 0
    wateringLevel = 0; // Инициализация уровня полива значением 0
}

// Функция имитации производства шерсти овцой
void Sheep::produceWool() {
    wool = true; // Установка наличия шерсти в true
}

// Функция проверки наличия шерсти у овцы
bool Sheep::getWool() {
    return wool;
}

// Функция установки статуса шерсти у овцы
void Sheep::setWool(bool _wool) {
    wool = _wool;
}

// Функция получения типа сущности (овца)
int Sheep::get_type() {
    return 4;
}

// Функция имитации роста овцы
bool Sheep::grow() {
    if (wateringLevel == 3 && hungryStatus == 3) {
        produceWool(); // Имитация производства шерсти при хорошем поливе и кормлении
        std::cout << "Овца готова к стрижке" << std::endl;
    }
    wateringLevel--;
    if (wateringLevel < 0) wateringLevel = 0;
    hungryStatus--;
    if (hungryStatus < 0) hungryStatus = 0;
    growthStage++;
    std::cout << "Овца выросла до возраста:" << growthStage << std::endl;
    return true;
}

// Функция полива овцы
void Sheep::water() {
    if (wateringLevel < 3) {
        wateringLevel++;
        std::cout << "Овца напоена до уровня: " << wateringLevel << std::endl;
        return;
    }
    else {
        std::cout << "Уровень полива =" << wateringLevel << " (овца уже напоена)" << std::endl;
    }
}