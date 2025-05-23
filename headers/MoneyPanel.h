#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Inventory.h"

class MoneyPanel {
Inventory* inventory;
public:
    MoneyPanel();
    bool loadResources();
    void setMoney(unsigned int money);
    void draw(sf::RenderWindow& window);
    void setPosition(float x, float y);
    void setInventory(Inventory* inventory);
    void updateFromInventory();

private:
    sf::Sprite panelSprite;
    sf::Texture panelTexture;
    sf::Text moneyText;
    sf::Font font;
    unsigned int currentMoney;
    Inventory* linkedInventory = nullptr;
};