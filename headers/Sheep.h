#pragma once
#ifndef SHEEP_H
#define SHEEP_H

#include "Animal.h"

// Объявление класса Sheep (Овца), который наследуется от класса Animal (Животное)
class Sheep : public Animal
{
private:
	bool wool; // Приватная переменная-член, указывающая, есть ли у овцы шерсть

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

	// Геттер для получения максимального уровня полива овцы  
	int get_maxWateringLevel() { return 3; };

	// Деструктор класса Sheep  
	~Sheep() {};
};

#endif  
