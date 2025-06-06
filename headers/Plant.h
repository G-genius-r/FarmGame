#pragma once

#ifndef PLANT_H
#define PLANT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "Entity.h"
#include "Inventory.h"
#include "NotificationPanel.h"

class Plant : public Entity
{
protected:
    // ����, �����������, ���� �� �������� ��������
    bool isFertilised;
private:
    NotificationPanel* notifPanel;
public:
    // ����������� ��� ������������� ������� Plant
    Plant();

    void setNotificationPanel(NotificationPanel* panel);

    // ������� ��� ��������� ��������
    void fertilise(Inventory* Inventory);

    // ������� ��� ��������, ������� �� ��������
    // ����������: true, ���� �������� �������, ����� false
    bool checkDeath();

    // ������� ��� ��������� ����������� ����� ����� �������� ��������
    // ����������: ���������� ��� ����� �������� ��������
    std::string getCorrectFilename();

    std::string getFertiliserSprite() const;

    // ����������� ������� ��� ��������� ���� �������� (������ ���� ����������� � ����������� �������)
    // ����������: ��� �������� (��������, 1 � �������, 2 � ������ � �. �.)
    virtual int get_type() = 0;

    // ����������� ������� ��� ��������� ����� �������� (������ ���� ����������� � ����������� �������)
    // ����������: true, ���� �������� �������, ����� false
    virtual bool grow() = 0;
};

#endif