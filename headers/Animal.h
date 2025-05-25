#pragma once
#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include "Entity.h"
#include "Inventory.h"

// ����� Animal, ����������� �� Entity, ������������ ������� ����� ��� ���� �������� � ����
class Animal : public Entity
{
protected:
    // ��� ��������� (��������, "������", "����")
    std::string type;

    // ����������������� ����� ��������� (� ����)
    int lifespan;

    // ��������, ��������� � ��������
    std::vector<std::string> textures;

public:
    // ������� ������� ��������� (����������� ������ ����)
    int hungryStatus;

    // ����������� ��� ������������� ������� Animal
    Animal();

    // ���������, ������ �� ��������
    // ����������: true, ���� �������� ������, ����� false
    bool checkDeath();

    // ������ �������� ������ �� ���������
    // ��������: Inventory - ��������� �� ���������
    // ����������: true, ���� �������� ������� ����������, ����� false
    bool eatGrain(Inventory* Inventory);

    // �������� ������� ������� ���������
    // ����������: ������� ���������
    int get_age();

    // ������������� ������� ���������
    // ��������: _age - ������� ��� ���������
    void set_age(int _age);

    // ����������� ������� ��� ��������� ���� ��������� (������ ���� ����������� � ����������� �������)
    // ����������: ��� ��������� (��������, 1 - ������, 2 - ����)
    virtual int get_type() = 0;

    // �������� ����������������� ����� ���������
    // ����������: ����������������� �����
    int get_lifespan();

    // ������������� ����������������� ����� ���������
    // ��������: _lifespan - ����������������� ����� ��� ���������
    void set_lifespan(int _lifespan);

    // �������� ������� ������� ������� ���������
    // ����������: ������� �������
    int get_hungryStatus();

    // ������������� ������� ������� ���������
    // ��������: _hungryStatus - ������� ������� ��� ���������
    void set_hungryStatus(int _hungryStatus);

    // ����������� ������� ��� ����� ��������� (������ ���� ����������� � ����������� �������)
    virtual bool grow() = 0;

    std::string getHungerSprite() const;

    // ���������� ������ Animal
    ~Animal();
};

#endif