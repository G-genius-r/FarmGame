#include "../headers/MoneyPanel.h"

MoneyPanel::MoneyPanel() : currentMoney(0) {}

bool MoneyPanel::loadResources() {
    // Загружаем текстуру панели
    if (!panelTexture.loadFromFile("sprites/money_background.png")) {
        return false;
    }
    panelSprite.setTexture(panelTexture);

    // Загружаем шрифт для текста
    if (!font.loadFromFile("Silkscreen/CyrilicOld.ttf")) {
        return false;
    }

    // Настраиваем текст
    moneyText.setFont(font);
    moneyText.setCharacterSize(35);
    moneyText.setFillColor(sf::Color::White);
    moneyText.setString(std::to_string(currentMoney));

    return true;
}

void MoneyPanel::setInventory(Inventory* inventory) {
    linkedInventory = inventory;
    if (inventory) {
        setMoney(inventory->getMoney());
    }
}

void MoneyPanel::updateFromInventory() {
    if (linkedInventory) {
        setMoney(linkedInventory->getMoney());
    }
}

void MoneyPanel::setMoney(unsigned int money) {
    currentMoney = money;
    moneyText.setString(std::to_string(currentMoney));

    // Можно добавить анимацию или эффекты при изменении денег
}

void MoneyPanel::draw(sf::RenderWindow& window) {
    window.draw(panelSprite);
    window.draw(moneyText);
}

void MoneyPanel::setPosition(float x, float y) {
    panelSprite.setPosition(x, y);
    // Текст можно позиционировать относительно панели
    float textOffsetX = 100 * 0.5f; // Умножаем отступы на масштаб
    float textOffsetY = 5 * 0.5f;
    moneyText.setPosition(x + textOffsetX, y + textOffsetY);
}