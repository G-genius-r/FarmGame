#pragma once
// GameState.cpp
#include "../headers/GameState.h"
#include <iostream>
#include <fstream>

bool GameState::saveToFile(const std::string& gameDataFilename, const std::string& inventoryFilename) const
{
    // ��������� ���������
    std::ofstream inventoryFile(inventoryFilename);
    if (!inventoryFile.is_open()) {
        std::cerr << "������ �������� ����� ��� ���������� Inventory: " << inventoryFilename << std::endl;
        return false;
    }
    if (!inventory.save(inventoryFile)) {
        std::cerr << "������ ���������� Inventory" << std::endl;
        return false;
    }
    inventoryFile.close();

    // ��������� ������ ����
    std::ofstream gameDataFile(gameDataFilename);
    if (!gameDataFile.is_open()) {
        std::cerr << "������ �������� ����� ��� ���������� ������ ����: " << gameDataFilename << std::endl;
        return false;
    }

    // TODO: ��������� ����� � ������ �������, ���� �����
    // ��������:
    // map.save(gameDataFile);

    gameDataFile.close();

    return true;
}

bool GameState::loadFromFile(const std::string& gameDataFilename, const std::string& inventoryFilename)
{
    // ��������� ���������
    std::ifstream inventoryFile(inventoryFilename);
    if (!inventoryFile.is_open()) {
        std::cerr << "������ �������� ����� ��� �������� Inventory: " << inventoryFilename << std::endl;
        return false;
    }
    if (!inventory.load(inventoryFile)) {
        std::cerr << "������ �������� Inventory" << std::endl;
        return false;
    }
    inventoryFile.close();

    // ��������� ������ ����
    std::ifstream gameDataFile(gameDataFilename);
    if (!gameDataFile.is_open()) {
        std::cerr << "������ �������� ����� ��� �������� ������ ����: " << gameDataFilename << std::endl;
        return false;
    }

    // TODO: ��������� ����� � ������ �������
    // ��������:
    // map.load(gameDataFile);

    gameDataFile.close();

    return true;
}