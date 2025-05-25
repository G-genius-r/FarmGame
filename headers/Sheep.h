#pragma once
#ifndef SHEEP_H
#define SHEEP_H

#include "Animal.h"

// Объявление класса Sheep (Овца), который наследуется от класса Animal (Животное)
class Sheep : public Animal
{
private:
	bool wool; // Наличие шерсти у овцы
	int waterLevelToDisplay; // Текущий уровень воды для отображения
	sf::Clock waterDisplayClock; // Таймер для отображения уровня воды
public:
	// Конструктор класса Sheep
	Sheep();

	// Метод для имитации производства шерсти овцой  
	void produceWool();

	// Геттер для получения статуса наличия шерсти  
	bool getWool();

	// Сеттер для установки статуса наличия шерсти  
	void setWool(bool _wool);

	// Метод для получения типа животного (предполагается, что он определен в классе Animal)  
	int get_type();

	// Метод для имитации роста овцы  
	bool grow();

	// Метод для полива овцы  
	void water();

	void showWaterLevel();

	// Отрисовать уровень воды
	void drawWaterLevel(sf::RenderWindow& window, float x, float y);

	// Получить максимальный уровень полива
	int get_maxWateringLevel() override { return 3; };

	// Деструктор класса Sheep  
	~Sheep() {};
};

#endif  
