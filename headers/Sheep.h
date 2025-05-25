#pragma once
#ifndef SHEEP_H
#define SHEEP_H

#include "Animal.h"

// ���������� ������ Sheep (����), ������� ����������� �� ������ Animal (��������)
class Sheep : public Animal
{
private:
	bool wool; // ������� ������ � ����
	int waterLevelToDisplay; // ������� ������� ���� ��� �����������
	sf::Clock waterDisplayClock; // ������ ��� ����������� ������ ����
public:
	// ����������� ������ Sheep
	Sheep();

	// ����� ��� �������� ������������ ������ �����  
	void produceWool();

	// ������ ��� ��������� ������� ������� ������  
	bool getWool();

	// ������ ��� ��������� ������� ������� ������  
	void setWool(bool _wool);

	// ����� ��� ��������� ���� ��������� (��������������, ��� �� ��������� � ������ Animal)  
	int get_type();

	// ����� ��� �������� ����� ����  
	bool grow();

	// ����� ��� ������ ����  
	void water();

	void showWaterLevel();

	// ���������� ������� ����
	void drawWaterLevel(sf::RenderWindow& window, float x, float y);

	// �������� ������������ ������� ������
	int get_maxWateringLevel() override { return 3; };

	// ���������� ������ Sheep  
	~Sheep() {};
};

#endif  
