#include "../headers/Chicken.h"
#include <iostream>

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
    waterLevelToDisplay = -1; // Инициализация индикатора уровня воды
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
        if (notifPanel) notifPanel->addMessage("Курица отложила яйцо");
    }

    wateringLevel--; // Уменьшает уровень полива
    if (wateringLevel < 0) wateringLevel = 0;

    hungryStatus--; // Уменьшает уровень голода
    if (hungryStatus < 0) hungryStatus = 0;

    growthStage++; // Увеличивает стадию роста
    if (notifPanel) notifPanel->addMessage("Курица выросла до возраста: " + std::to_string(growthStage));
    return true; // Возвращает true для подтверждения роста
}

// Функция для симуляции полива курицы
void Chicken::water() {
    if (wateringLevel < 3) {
        wateringLevel++; // Увеличивает уровень полива
        showWaterLevel();
    }
    // В любом случае показываем уровень влаги над курицей
    waterLevelToDisplay = wateringLevel;
    waterDisplayClock.restart();
}

void Chicken::showWaterLevel() {
    waterLevelToDisplay = wateringLevel;
    waterDisplayClock.restart();
}

void Chicken::drawWaterLevel(sf::RenderWindow& window, float x, float y) {
    if (waterLevelToDisplay != -1 && waterDisplayClock.getElapsedTime().asSeconds() < 1.0f) {
        static sf::Font font;
        static bool fontLoaded = false;
        if (!fontLoaded) {
            font.loadFromFile("Silkscreen/CyrilicOld.ttf");
            fontLoaded = true;
        }
        sf::Text txt("Вода: " + std::to_string(wateringLevel), font, 20);
        txt.setFillColor(sf::Color::Blue);
        txt.setPosition(x, y - 25);
        window.draw(txt);
    }
    else if (waterLevelToDisplay != -1) {
        waterLevelToDisplay = -1;
    }
}