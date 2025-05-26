#pragma once
// GameState.cpp
#include "../headers/GameState.h"
#include <iostream>
#include <fstream>

bool GameState::saveToFile(const std::string& gameDataFilename, const std::string& inventoryFilename) const
{
    // Сохраняем инвентарь
    std::ofstream inventoryFile(inventoryFilename);
    if (!inventoryFile.is_open()) {
        std::cerr << "Ошибка открытия файла для сохранения Inventory: " << inventoryFilename << std::endl;
        return false;
    }
    if (!inventory.save(inventoryFile)) {
        std::cerr << "Ошибка сохранения Inventory" << std::endl;
        return false;
    }
    inventoryFile.close();

    // Сохраняем данные игры
    std::ofstream gameDataFile(gameDataFilename);
    if (!gameDataFile.is_open()) {
        std::cerr << "Ошибка открытия файла для сохранения данных игры: " << gameDataFilename << std::endl;
        return false;
    }

    // TODO: сохранить карту и другие объекты, если нужно
    // Например:
    // map.save(gameDataFile);

    gameDataFile.close();

    return true;
}

bool GameState::loadFromFile(const std::string& gameDataFilename, const std::string& inventoryFilename)
{
    // Загружаем инвентарь
    std::ifstream inventoryFile(inventoryFilename);
    if (!inventoryFile.is_open()) {
        std::cerr << "Ошибка открытия файла для загрузки Inventory: " << inventoryFilename << std::endl;
        return false;
    }
    if (!inventory.load(inventoryFile)) {
        std::cerr << "Ошибка загрузки Inventory" << std::endl;
        return false;
    }
    inventoryFile.close();

    // Загружаем данные игры
    std::ifstream gameDataFile(gameDataFilename);
    if (!gameDataFile.is_open()) {
        std::cerr << "Ошибка открытия файла для загрузки данных игры: " << gameDataFilename << std::endl;
        return false;
    }

    // TODO: загрузить карту и другие объекты
    // Например:
    // map.load(gameDataFile);

    gameDataFile.close();

    return true;
}