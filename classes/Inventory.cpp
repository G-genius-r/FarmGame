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

// ��������� ������ ��������� � ����
bool Inventory::saveDataToFile(const std::string& filename)
{
    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
        std::cerr << "������ �������� �����: " << filename << std::endl;
        return false;
    }

    // ������ ������ ��������� � ����
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

// ��������� ������ ��������� �� �����
bool Inventory::loadDataFromFile(const std::string& filename)
{
    std::ifstream inFile(filename);
    if (!inFile.is_open())
    {
        std::cerr << "������ �������� �����: " << filename << std::endl;
        return false;
    }

    // ������ ������ ��������� �� �����
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

// ���������� ��������� �� ������
bool Inventory::show(sf::RenderWindow* window)
{
    std::string texture_filename = "sprites/Inventory_backdrop.png";

    if (!backdrop_texture.loadFromFile(texture_filename))
    {
        std::cout << "������ �������� �������� �� �����: " << texture_filename << "." << std::endl;
        return false;
    }

    backdrop_sprite.setTexture(backdrop_texture);
    backdrop_sprite.setPosition(sf::Vector2f(inventoryPos_x, inventoryPos_y));
    window->draw(backdrop_sprite);

    displayInvText(window, "~���������~", inventoryPos_x + 30, inventoryPos_y + 20);

    // ������ � ����� ��� �����
    sf::Texture moneyTexture;
    if (!moneyTexture.loadFromFile("sprites/inventorySprite/moneySprite.png")) {
        std::cout << "������ �������� moneySprite.png" << std::endl;
    }
    sf::Sprite moneySprite;
    moneySprite.setTexture(moneyTexture);
    moneySprite.setPosition(inventoryPos_x + 8, inventoryPos_y + 38);
    window->draw(moneySprite);

    displayInvText(window, "������: ", inventoryPos_x + 27, inventoryPos_y + 40);
    displayInvText(window, std::to_string(money), inventoryPos_x + 120, inventoryPos_y + 40);

    // ������ � ����� ��� ���������
    sf::Texture fertiliserTexture;
    if (!fertiliserTexture.loadFromFile("sprites/inventorySprite/fertiliserSprite.png")) {
        std::cout << "������ �������� fertiliserSprite.png" << std::endl;
    }
    sf::Sprite fertiliserSprite;
    fertiliserSprite.setTexture(fertiliserTexture);
    fertiliserSprite.setPosition(inventoryPos_x + 8, inventoryPos_y + 58);
    window->draw(fertiliserSprite);

    displayInvText(window, "���������: ", inventoryPos_x + 27, inventoryPos_y + 60);
    displayInvText(window, std::to_string(fertiliser), inventoryPos_x + 120, inventoryPos_y + 60);

    // �������� ������� � ������ ��� ����� ��������
    sf::Texture animalFeedTexture;
    if (!animalFeedTexture.loadFromFile("sprites/inventorySprite/animalFeed.png")) {
        std::cout << "������ �������� wheatSeed.png" << std::endl;
    }
    sf::Sprite animalFeedSprite;
    animalFeedSprite.setTexture(animalFeedTexture);
    animalFeedSprite.setPosition(inventoryPos_x + 8, inventoryPos_y + 78);
    window->draw(animalFeedSprite);

    displayInvText(window, "���� ��� ��������: ", inventoryPos_x + 27, inventoryPos_y + 80);
    displayInvText(window, std::to_string(animalFeed), inventoryPos_x + 120, inventoryPos_y + 80);

    // �������� ������� � ������ ��� ����� �������
    sf::Texture wheatGrainTexture;
    if (!wheatGrainTexture.loadFromFile("sprites/wheatSprite/wheatItem.png")) {
        std::cout << "������ �������� wheatItem.png" << std::endl;
    }
    sf::Sprite wheatGrainSprite;
    wheatGrainSprite.setTexture(wheatGrainTexture);
    wheatGrainSprite.setPosition(inventoryPos_x + 8, inventoryPos_y + 98);
    window->draw(wheatGrainSprite);

    displayInvText(window, "����� �������: ", inventoryPos_x + 27, inventoryPos_y + 100);
    displayInvText(window, std::to_string(wheatGrain), inventoryPos_x + 120, inventoryPos_y + 100);

    // �������� ������� � ������ ��� ����� ������
    sf::Texture barleyGrainTexture;
    if (!barleyGrainTexture.loadFromFile("sprites/barleySprite/barleyItem.png")) {
        std::cout << "������ �������� barleyItem.png" << std::endl;
    }
    sf::Sprite barleyGrainSprite;
    barleyGrainSprite.setTexture(barleyGrainTexture);
    barleyGrainSprite.setPosition(inventoryPos_x + 8, inventoryPos_y + 118);
    window->draw(barleyGrainSprite);

    displayInvText(window, "����� ������: ", inventoryPos_x + 27, inventoryPos_y + 120);
    displayInvText(window, std::to_string(barleyGrain), inventoryPos_x + 120, inventoryPos_y + 120);

    // �������� ������� � ������ ��� ����� �������
    sf::Texture wheatSeedTexture;
    if (!wheatSeedTexture.loadFromFile("sprites/wheatSprite/wheatSeed.png")) {
        std::cout << "������ �������� wheatSeed.png" << std::endl;
    }
    sf::Sprite wheatSeedSprite;
    wheatSeedSprite.setTexture(wheatSeedTexture);
    wheatSeedSprite.setPosition(inventoryPos_x + 8, inventoryPos_y + 138);
    window->draw(wheatSeedSprite);

    displayInvText(window, "������ �������: ", inventoryPos_x + 27, inventoryPos_y + 140);
    displayInvText(window, std::to_string(wheatSeed), inventoryPos_x + 120, inventoryPos_y + 140);

    // �������� ������� � ������ ��� ����� ������
    sf::Texture barleySeedTexture;
    if (!barleySeedTexture.loadFromFile("sprites/barleySprite/barleySeed.png")) {
        std::cout << "������ �������� barleySeed.png" << std::endl;
    }
    sf::Sprite barleySeedSprite;
    barleySeedSprite.setTexture(barleySeedTexture);
    barleySeedSprite.setPosition(inventoryPos_x + 8, inventoryPos_y + 158);
    window->draw(barleySeedSprite);

    displayInvText(window, "������ ������: ", inventoryPos_x + 27, inventoryPos_y + 160);
    displayInvText(window, std::to_string(barleySeed), inventoryPos_x + 120, inventoryPos_y + 160);

    // �������� ������� � ������ ��� ������
    sf::Texture woolIconTexture;
    if (!woolIconTexture.loadFromFile("sprites/inventorySprite/woolIcon.png")) {
        std::cout << "������ �������� woolIcon.png" << std::endl;
    }
    sf::Sprite woolIconSprite;
    woolIconSprite.setTexture(woolIconTexture);
    woolIconSprite.setPosition(inventoryPos_x + 8, inventoryPos_y + 178);
    window->draw(woolIconSprite);

    displayInvText(window, "������: ", inventoryPos_x + 27, inventoryPos_y + 180);
    displayInvText(window, std::to_string(wool), inventoryPos_x + 120, inventoryPos_y + 180);

    // �������� ������� � ������ ��� ���
    sf::Texture eggIconTexture;
    if (!eggIconTexture.loadFromFile("sprites/chickenSprite/eggIcon.png")) {
        std::cout << "������ �������� eggIcon.png" << std::endl;
    }
    sf::Sprite eggIconSprite;
    eggIconSprite.setTexture(eggIconTexture);
    eggIconSprite.setPosition(inventoryPos_x + 8, inventoryPos_y + 198);
    window->draw(eggIconSprite);

    displayInvText(window, "����: ", inventoryPos_x + 27, inventoryPos_y + 200);
    displayInvText(window, std::to_string(eggs), inventoryPos_x + 120, inventoryPos_y + 200);

    // �������� ������� � ������ ��� ���
    sf::Texture chickenIconTexture;
    if (!chickenIconTexture.loadFromFile("sprites/chickenSprite/chickenSprite1.png")) {
        std::cout << "������ �������� chickenSprite1.png" << std::endl;
    }
    sf::Sprite chickenIconSprite;
    chickenIconSprite.setTexture(chickenIconTexture);
    chickenIconSprite.setPosition(inventoryPos_x + 8, inventoryPos_y + 218);
    window->draw(chickenIconSprite);

    displayInvText(window, "����: ", inventoryPos_x + 27, inventoryPos_y + 220);
    displayInvText(window, std::to_string(chickens), inventoryPos_x + 120, inventoryPos_y + 220);

    // �������� ������� � ������ ��� ����
    sf::Texture sheepIconTexture;
    if (!sheepIconTexture.loadFromFile("sprites/sheepSprite/sheepSprite.png")) {
        std::cout << "������ �������� sheepSprite.png" << std::endl;
    }
    sf::Sprite sheepIconSprite;
    sheepIconSprite.setTexture(sheepIconTexture);
    sheepIconSprite.setPosition(inventoryPos_x + 8, inventoryPos_y + 238);
    window->draw(sheepIconSprite);

    displayInvText(window, "����: ", inventoryPos_x + 27, inventoryPos_y + 240);
    displayInvText(window, std::to_string(sheep), inventoryPos_x + 120, inventoryPos_y + 240);

    // �������� ������� � ������ ��� ����
    sf::Texture meatIconTexture;
    if (!meatIconTexture.loadFromFile("sprites/inventorySprite/meatIcon.png")) {
        std::cout << "������ �������� meatIcon.png" << std::endl;
    }
    sf::Sprite meatIconSprite;
    meatIconSprite.setTexture(meatIconTexture);
    meatIconSprite.setPosition(inventoryPos_x + 8, inventoryPos_y + 258);
    window->draw(meatIconSprite);

    displayInvText(window, "����: ", inventoryPos_x + 27, inventoryPos_y + 260);
    displayInvText(window, std::to_string(meat), inventoryPos_x + 120, inventoryPos_y + 260);
    return (1);
}

void Inventory::displayInvText(sf::RenderWindow* window, std::string displayString, int x, int y)
{
    sf::Font font;
    font.loadFromFile("Silkscreen/CyrilicOld.ttf");

    sf::Text text;
    text.setFont(font);
    text.setString(displayString);
    text.setCharacterSize(10);
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
    std::cout << "�� �������� " << amount << " ������ �������." << std::endl;
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
int Inventory::getMoney()
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