#include "../headers/Plant.h"

// Конструктор класса Plant
Plant::Plant() {
    growthStage = 0; // Стадия роста  
    wateringLevel = 0; // Уровень полива
    isFertilised = false; // Инициализация статуса удобрения как false  
    isPlant = true; // Установка флага, что это растение  
    isAnimal = false; // Установка флага, что это не животное  
}

// Функция для удобрения растения  
void Plant::fertilise(Inventory* Inventory) {
    if (isFertilised == true) {
        std::cout << "Растение уже было удобрено." << std::endl;
        Inventory->fertiliserAdd(1); // Добавление удобрения в инвентарь  
        return;
    }
    isFertilised = true; // Отметка, что растение удобрено  
    std::cout << "Растение было удобрено." << std::endl;
}

// Функция для симуляции роста растения  
bool Plant::grow() {
    if (wateringLevel == 5 && isFertilised) {
        growthStage++; // Увеличение стадии роста  
        wateringLevel--; // Уменьшение уровня полива  
        return true; // Возврат true, если рост успешен  
    }
    wateringLevel--; // Уменьшение уровня полива  
    return false; // Возврат false, если условия для роста не выполнены  
}

// Функция для проверки, погибло ли растение из-за недостатка воды  
bool Plant::checkDeath() {
    if (this->get_isWatered() == 0) {
        std::cout << "О нет! Растение погибло." << std::endl;
        return true; // Возврат true, если растение погибло  
    }
    else {
        return false; // Возврат false, если растение еще живо  
    }
}

std::string Plant::getFertiliserSprite() const {
    if (!isFertilised)
        return "sprites/inventorySprite/fertiliserSprite.png";
    else
        return "";
}