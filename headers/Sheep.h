#pragma once
#ifndef SHEEP_H
#define SHEEP_H

#include "Animal.h"

// ���������� ������ Sheep (����), ������� ����������� �� ������ Animal (��������)
class Sheep : public Animal
{
private:
	bool wool; // ��������� ����������-����, �����������, ���� �� � ���� ������

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

	// ������ ��� ��������� ������������� ������ ������ ����  
	int get_maxWateringLevel() { return 3; };

	// ���������� ������ Sheep  
	~Sheep() {};
};

#endif  
