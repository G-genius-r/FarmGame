#include "../headers/Inventory.h"
#include <stdio.h>
#include <fstream>

Inventory::Inventory()
{
    money = 100;
    fertiliser = 0;
    animalFeed = 0;
    wheatGrain = 0;
    barleyGrain = 0;
    wheatSeed = 4;
    barleySeed = 0;
    wool = 0;
    eggs = 0;
    chickens = 0;
    sheep = 0;
    meat = 0;

    inventoryPos_x = 0;
    inventoryPos_y = 0;
}

// Сохраняет данные инвентаря в файл
bool Inventory::saveDataToFile(const std::string& filename)
{
    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return false;
    }

    // Запись данных инвентаря в файл
    outFile << money << std::endl;
    outFile << fertiliser << std::endl;
    outFile << animalFeed << std::endl;
    outFile << wheatGrain << std::endl;
    outFile << barleyGrain << std::endl;
    outFile << wheatSeed << std::endl;
    outFile << barleySeed << std::endl;
    outFile << wool << std::endl;
    outFile << eggs << std::endl;
    outFile << chickens << std::endl;
    outFile << sheep << std::endl;
    outFile << meat << std::endl;

    outFile.close();
    return true;
}

// Загружает данные инвентаря из файла
bool Inventory::loadDataFromFile(const std::string& filename)
{
    std::ifstream inFile(filename);
    if (!inFile.is_open())
    {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return false;
    }

    // Чтение данных инвентаря из файла
    inFile >> money;
    inFile >> fertiliser;
    inFile >> animalFeed;
    inFile >> wheatGrain;
    inFile >> barleyGrain;
    inFile >> wheatSeed;
    inFile >> barleySeed;
    inFile >> wool;
    inFile >> eggs;
    inFile >> chickens;
    inFile >> sheep;
    inFile >> meat;

    inFile.close();
    return true;
}

// Отображает инвентарь на экране
bool Inventory::show(sf::RenderWindow* window)
{
    constexpr int winW = 800, winH = 800;
    constexpr int invW = 280, invH = 680;
    inventoryPos_x = 16; // Левый край, небольшой отступ
    inventoryPos_y = (winH - invH) / 2;

    std::string texture_filename = "sprites/Inventory_backdrop.png";
    if (!backdrop_texture.loadFromFile(texture_filename))
    {
        std::cout << "Ошибка загрузки текстуры из файла: " << texture_filename << "." << std::endl;
        return false;
    }

    backdrop_sprite.setTexture(backdrop_texture);
    backdrop_sprite.setPosition(sf::Vector2f(inventoryPos_x, inventoryPos_y));
    backdrop_sprite.setScale(
        float(invW) / backdrop_texture.getSize().x,
        float(invH) / backdrop_texture.getSize().y
    );
    window->draw(backdrop_sprite);

    displayInvText(window, "~ИНВЕНТАРЬ~", inventoryPos_x + 40, inventoryPos_y + 18);

    struct ItemEntry {
        const char* label;
        const char* iconPath;
        int* value;
    } items[] = {
        {"деньги:", "sprites/inventorySprite/moneySprite.png", &money},
        {"удобрение:", "sprites/fertilizer.png", &fertiliser},
        {"корм для животных:", "sprites/inventorySprite/animalFeed.png", &animalFeed},
        {"зерно пшеницы:", "sprites/wheatSprite/wheatItem.png", &wheatGrain},
        {"зерно ячменя:", "sprites/barleySprite/barleyItem.png", &barleyGrain},
        {"семена пшеницы:", "sprites/wheatSprite/wheatSeed.png", &wheatSeed},
        {"семена ячменя:", "sprites/barleySprite/barleySeed.png", &barleySeed},
        {"шерсть:", "sprites/inventorySprite/woolIcon.png", &wool},
        {"яйца:", "sprites/chickenSprite/eggIcon.png", &eggs},
        {"куры:", "sprites/chickenSprite/chickenSprite1.png", &chickens},
        {"овцы:", "sprites/sheepSprite/sheepSprite.png", &sheep},
        {"мясо:", "sprites/inventorySprite/meatIcon.png", &meat},
    };

    const int iconSize = 26;
    const int xIcon = inventoryPos_x + 12;
    const int xLabel = inventoryPos_x + 46;
    const int xValue = inventoryPos_x + invW - 44;
    const int yStart = inventoryPos_y + 52;
    const int yStep = 50; // Сделано с запасом под шрифт и иконку

    for (int i = 0; i < sizeof(items) / sizeof(ItemEntry); ++i) {
        int y = yStart + i * yStep;

        // Load icon
        sf::Texture texture;
        if (!texture.loadFromFile(items[i].iconPath)) {
            std::cout << "Ошибка загрузки " << items[i].iconPath << std::endl;
        }
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setPosition(xIcon, y);
        sprite.setScale(float(iconSize) / texture.getSize().x, float(iconSize) / texture.getSize().y);
        window->draw(sprite);

        // Draw text
        displayInvText(window, items[i].label, xLabel, y + 4);
        displayInvText(window, std::to_string(*items[i].value), xValue, y + 4);
    }
    return true;
}

void Inventory::displayInvText(sf::RenderWindow* window, std::string displayString, int x, int y)
{
    static sf::Font font;
    static bool loaded = false;
    if (!loaded) {
        font.loadFromFile("Silkscreen/CyrilicOld.ttf");
        loaded = true;
    }

    sf::Text text;
    text.setFont(font);
    text.setString(displayString);
    text.setCharacterSize(16); // Четко видно для 800x800
    text.setFillColor(sf::Color::Black);
    text.setPosition(x, y);
    window->draw(text);
}

void Inventory::moneyAdd(int amount)
{
    money += amount;
}

bool Inventory::moneyTake(int amount)
{
    if (money - amount < 0)
        return (0);
    else
        money -= amount;
    return (1);
}

void Inventory::fertiliserAdd(int amount)
{
    fertiliser += amount;
}

bool Inventory::fertiliserTake(int amount)
{
    if (fertiliser - amount < 0)
        return false;

    fertiliser -= amount;
    return true;
}

void Inventory::wheatGrainAdd(int amount)
{
    std::cout << "Вы получили " << amount << " единиц пшеницы." << std::endl;
    wheatGrain += amount;
}

bool Inventory::wheatGrainTake(int amount)
{
    if (wheatGrain - amount < 0)
        return false;

    wheatGrain -= amount;
    return true;
}

void Inventory::barleyGrainAdd(int amount)
{
    barleyGrain += amount;
}

bool Inventory::barleyGrainTake(int amount)
{
    if (barleyGrain - amount < 0)
        return false;

    barleyGrain -= amount;
    return true;
}

void Inventory::wheatSeedAdd(int amount)
{
    wheatSeed += amount;
}

bool Inventory::wheatSeedTake(int amount)
{
    if (wheatSeed - amount < 0)
        return false;

    wheatSeed -= amount;
    return true;
}
void Inventory::barleySeedAdd(int amount)
{
    barleySeed += amount;
}

bool Inventory::barleySeedTake(int amount)
{
    if (barleySeed - amount < 0)
        return false;

    barleySeed -= amount;
    return true;
}
void Inventory::woolAdd(int amount)
{
    wool += amount;
}

bool Inventory::woolTake(int amount)
{
    if (wool - amount < 0)
        return false;

    wool -= amount;
    return true;
}

void Inventory::eggsAdd(int amount)
{
    eggs += amount;
}

bool Inventory::eggsTake(int amount)
{
    if (eggs - amount < 0)
        return false;

    eggs -= amount;
    return true;
}
unsigned int Inventory::getMoney()
{
    return money;
}

void Inventory::ChickenAdd(int amount)
{
    chickens += amount;
}

bool Inventory::ChickenTake(int amount)
{
    if (chickens - amount < 0)
        return false;

    chickens -= amount;
    return true;
}
void Inventory::SheepAdd(int amount)
{
    sheep += amount;
}

bool Inventory::SheepTake(int amount)
{
    if (sheep - amount < 0)
        return false;

    sheep -= amount;
    return true;
}

int Inventory::getWool()
{
    return wool;
}
int Inventory::getEggs()
{
    return eggs;
}
int Inventory::getWheatGrain()
{
    return wheatGrain;
}
int Inventory::getBarleyGrain()
{
    return barleyGrain;
}
void Inventory::animalFeedAdd(int amount)
{
    animalFeed += amount;
}
bool Inventory::animalFeedTake(int amount)
{
    if (animalFeed - amount < 0)
    {
        return false;
    }
    animalFeed -= amount;
    return true;
}
int Inventory::getMeat()
{
    return meat;
}
void Inventory::meatAdd(int amount)
{
    meat += amount;
}
bool Inventory::meatTake(int amount)
{
    if (meat - amount < 0)
    {
        return false;
    }
    meat -= amount;
    return true;
}