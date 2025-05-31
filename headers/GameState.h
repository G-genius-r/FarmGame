#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <fstream>
#include "Inventory.h"
#include "Farm.h"


class GameState
{

public:
    Inventory inventory;

    // Например, сюда можно добавить карту:
    // Map map;

    bool saveToFile(const std::string& gameDataFilename, const std::string& inventoryFilename) const;
    bool loadFromFile(const std::string& gameDataFilename, const std::string& inventoryFilename);
};