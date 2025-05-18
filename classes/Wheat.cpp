#include "../headers/Wheat.h"
#include "../headers/Barley.h"

Wheat::Wheat() {
    growthStage = 0;
    wateringLevel = 0;
    isFertilised = false;
    textureFilenames.push_back("sprites/wheatSprite/wheat0.png");
    textureFilenames.push_back("sprites/wheatSprite/wheat1.png");
    textureFilenames.push_back("sprites/wheatSprite/wheat2.png");
    textureFilenames.push_back("sprites/wheatSprite/wheat3.png");
    textureFilenames.push_back("sprites/wheatSprite/wheat0watered.png");
    textureFilenames.push_back("sprites/wheatSprite/wheat1watered.png");
    textureFilenames.push_back("sprites/wheatSprite/wheat2watered.png");
    std::cout << "Создано растение пшеницы." << std::endl;
}

int Wheat::get_type() {
    return 1;
}

void Wheat::water() {
    if (wateringLevel < 5) {
        wateringLevel++;
        std::cout << "Растение пшеницы полито. Уровень влаги: " << wateringLevel << std::endl;
        return;
    }
    else {
        std::cout << "Уровень влаги = " << wateringLevel << " (пшеница уже полита)" << std::endl;
    }
}

bool Wheat::grow() {
    /* Условия для роста */
    if (growthStage < 3 && wateringLevel == 5 && isFertilised) {
        growthStage++;
        std::cout << "Растение пшеницы выросло на следующую стадию!" << std::endl;
        wateringLevel--;
        return true;
    }
    else if (growthStage == 3) {
        std::cout << "Растение пшеницы достигло максимальной стадии роста!" << std::endl;
    }
    wateringLevel--;
    return false;
}