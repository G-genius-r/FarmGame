#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Farm.h"
#include "NotificationPanel.h"

//bool loadInventoryDataFromFile(const std::string& filename, Farm& farm, NotificationPanel& notifPanel);

bool showMenu(sf::RenderWindow& window, bool& musicOn, Farm& farm, NotificationPanel& notifPanel);

