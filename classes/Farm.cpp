#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "../headers/Farm.h"
#include <vector>
#include "../headers/NotificationPanel.h"
#include "../headers/Button.h"
#include "../headers/Wheat.h"
#include "../headers/Barley.h"
#include "../headers/Chicken.h"
#include "../headers/Sheep.h"
#include <cmath>

// ����������� ������ Farm
Farm::Farm()
{
    gridLength = 10; // ��������� ������� �����
    dayCounter = 1;  // ������������� �������� ����
    setBackTiles();  // �������� ������� ������
    setPlots();      // �������� �������� �����
    shop = new Shop(); // ������������� ��������
    inventory = new Inventory(); // ������������� ���������
    help_x = 20;     // ������� ���� ������ �� X
    help_y = 0;      // ������� ���� ������ �� Y
}

// �������� �������� �����
void Farm::setPlots()
{
    plots.clear(); // ������� ������������ ��������
    sf::Vector2f start(2, 3); // ��������� ���������� ��������
    sf::Vector2f end(7, 6);   // �������� ���������� ��������

    // �������� ����� ��������
    for (int x = 0; x <= end.x - start.x; x++)
    {
        std::vector<Plot*> pRow;
        for (int y = 0; y <= end.y - start.y; y++)
        {
            Plot* plot = new Plot("sprites/Transparent.png", 80 * (start.x + x), 80 * (start.y + y));
            plot->setUpFrontSprite("sprites/Transparent.png");
            pRow.push_back(plot);
        }
        plots.push_back(pRow);
    }
}

// �������� ������� ������
void Farm::setBackTiles()
{
    tiles.clear();
    for (int i = 0; i < gridLength; i++)
    {
        std::vector<GameTile*> row;
        for (int j = 0; j < gridLength; j++)
        {
            row.push_back(new GameTile("sprites/Transparent.png", 80 * i, 80 * j));
        }
        tiles.push_back(row);
    }
    std::cout << "������� ������ �������" << std::endl;
}

// ������� �� ��������� ����
void Farm::passTime(sf::RenderWindow* window)
{
    dayCounter++;

    // ���������� ���� ��������
    for (auto& row : plots)
    {
        for (auto& plot : row)
        {
            if (!plot->isEmpty() && !plot->checkDeath())
            {
                plot->growEntity(); // ���� ��������/���������
                plot->updateSprite();
            }
        }
    }

    // �������� �������� ���
    sf::Vector2u windowSize = window->getSize();

    sf::RectangleShape dayScreen;
    dayScreen.setFillColor(sf::Color::White);
    dayScreen.setSize(sf::Vector2f(windowSize.x, windowSize.y));
    window->draw(dayScreen);

    // ��������� ������ "����: N"
    std::string dayText = "����: " + std::to_string(dayCounter);

    // �������� ������ � ������ ������ (��������������, ��� displayFarmText ���������� ������ ������)
    sf::Font font;
    font.loadFromFile("Silkscreen/CyrilicOld.ttf"); 
    sf::Text text(dayText, font, 48); 
    text.setFillColor(sf::Color::Black);

    // ���������� ����� �� ����
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

    window->draw(text);

    window->display();
    pause(2); // ����� 2 �������
}

// ����� � ����
void Farm::pause(int num_seconds)
{
    sf::Clock clock;
    while (clock.getElapsedTime().asSeconds() < num_seconds);
}

// ��������� �������� ����
void Farm::drawDayCounter(sf::RenderWindow* window)
{
    sf::Font font;
    if (!font.loadFromFile("Silkscreen/CyrilicOld.ttf"))
    {
        std::cout << "������ �������� ������" << std::endl;
        return;
    }

    std::string dayText = "����: " + std::to_string(dayCounter);

    sf::Text text(dayText, font, 32);
    text.setFillColor(sf::Color(220, 185, 138));

    // �������
    text.setOutlineColor(sf::Color::White); // ������ �������
    text.setOutlineThickness(3.f); // ������� �������

    sf::Vector2u windowSize = window->getSize();
    sf::FloatRect textRect = text.getLocalBounds();

    float rightMargin = 20.f;
    float posX = windowSize.x - textRect.width - rightMargin;
    float posY = 70.f;

    text.setPosition(posX, posY);

    window->draw(text);
}

// ��������� �������� �������
bool Farm::changeBackSprite(int x, int y, std::string textureFilename)
{
    return tiles[y][x]->setUpBackSprite(textureFilename);
}

// ���� ������
bool Farm::get_Help(sf::RenderWindow* window)
{
    if (!Help_texture.loadFromFile("sprites/Shop_background.png"))
    {
        std::cout << "������ �������� �������� ������" << std::endl;
        return false;
    }
    Help_sprite.setTexture(Help_texture);
    float scaleX = window->getSize().x / static_cast<float>(Help_texture.getSize().x);
    float scaleY = window->getSize().y / static_cast<float>(Help_texture.getSize().y);
    Help_sprite.setScale(scaleX, scaleY);
    window->draw(Help_sprite);

    // ����� ������
    std::vector<sf::String> helpText = {
    "���� ������",
    "������� 'B' ��� �������� ��������",
    "������� 'I' ��� �������� ���������",
    "������� 'P' ��� �������� �� ��������� ����",
    "�������� ����� �������� ������ ����,",
    "�������� ������ ���� ��� �� �����.",
    "�������� ����� ����� � ������� ���������.",
    "��� ����� ��� ��� ������",
    "����������� ����� '�������'.",
    "���� �������� ��� ��������",
    "�� �������� ���� ��� ��� - ��� ��������.",
    "���� ����� 10 ����, ���� - 15 ����.",
    "����� � ����������!"
    };

    // ��������� ������ ������
    for (size_t i = 0; i < helpText.size(); i++)
    {
        displayFarmText(window, helpText[i], help_x + 25, help_y + 20 + i * 20);
    }

    return true;
}

// ����������� ����� ��� �������
void Farm::getPlotOptions(sf::RenderWindow* window, float pos_x, float pos_y)
{
    pos_x -= 1.8;
    pos_y -= 2.3;

    if (plots[pos_x][pos_y]->isEmpty())
    {
        // ����� ��� ������� �������
        std::vector<std::string> options = {
            "���� ������� ����.",
            "1 - �������� ������� (������ �������)",
            "2 - �������� ������ (������ ������)",
            "3 - �������� ������ (��������� ������)",
            "4 - �������� ���� (��������� ����)"
        };
        for (size_t i = 0; i < options.size(); i++)
        {
            displayFarmText(window, options[i], pos_x * 32, pos_y * 32 + i * 15);
        }
    }
    else if (plots[pos_x][pos_y]->get_isAnimal())
    {
        // ����� ��� ��������
        std::vector<std::string> options = {
            "1 - ���� ����",
            "2 - ���������",
            "3 - ������� (����/������)",
            "4 - ������"
        };
        for (size_t i = 0; i < options.size(); i++)
        {
            displayFarmText(window, options[i], pos_x * 32, pos_y * 32 + i * 15);
        }
    }
    else if (plots[pos_x][pos_y]->get_isPlant())
    {
        // ����� ��� ��������
        std::vector<std::string> options = {
            "1 - ������",
            "2 - ��������",
            "3 - ������� ������"
        };
        for (size_t i = 0; i < options.size(); i++)
        {
            displayFarmText(window, options[i], pos_x * 32, pos_y * 32 + i * 15);
        }
    }
}

// ��������, �������� �� ������ ��������
bool Farm::selectedTileIsPlot(sf::Vector2f selectedGametile)
{
    int tile_x = selectedGametile.x;
    int tile_y = selectedGametile.y;
    return (tile_x >= 2 && tile_x <= 7 && tile_y >= 3 && tile_y <= 6);
}

void Farm::clearPlotOptionButtons() {
    plotOptionButtons.clear();
}

int Farm::getGridLength() const {
    return gridLength;
}

// ����������� ������ �� �����
void Farm::displayFarmText(sf::RenderWindow* window, std::string text, int x, int y)
{
    sf::Font font;
    if (!font.loadFromFile("Silkscreen/CyrilicOld.ttf"))
    {
        std::cout << "������ �������� ������" << std::endl;
        return;
    }

    sf::Vector2u windowSize = window->getSize();

    unsigned int fontSize = static_cast<unsigned int>(windowSize.y * 0.03f);
    if (fontSize < 8) fontSize = 8;

    float posX = static_cast<float>(x) / 350.0f * windowSize.x;
    float posY = static_cast<float>(y) / 350.0f * windowSize.y;

    sf::Text sfText;
    sfText.setFont(font);
    sfText.setString(text);
    sfText.setCharacterSize(fontSize);
    sfText.setFillColor(sf::Color::White);
    sfText.setOutlineColor(sf::Color(220, 185, 138)); // ������ �������
    sfText.setOutlineThickness(3.f);
    sfText.setPosition(posX, posY);
    window->draw(sfText);
}

// ��������� ���� ��������
void Farm::drawPlots(sf::RenderWindow* window)
{
    sf::Vector2u windowSize = window->getSize();
    int plotsX = plots.size();
    int plotsY = plots[0].size();

    // ������ ����� ������ (�������) �� ������
    float cellWidth = windowSize.x / static_cast<float>(gridLength);
    float cellHeight = windowSize.y / static_cast<float>(gridLength);

    // ��������� ������� �������� (��������, 2,3 ��� � setPlots)
    int startX = 2;
    int startY = 3;

    for (int x = 0; x < plotsX; ++x)
    {
        for (int y = 0; y < plotsY; ++y)
        {
            Plot* plot = plots[x][y];
            // �������� �������
            sf::Sprite backSprite = plot->get_backSprite();
            sf::Sprite frontSprite = plot->get_frontSprite();

            // ��������� ������� ��� ����� �������
            float posX = (startX + x) * cellWidth;
            float posY = (startY + y) * cellHeight;

            // ������������ ������� ��� ������ ������ (�������)
            const sf::Texture* tex = backSprite.getTexture();
            if (tex) {
                float tW = static_cast<float>(tex->getSize().x);
                float tH = static_cast<float>(tex->getSize().y);

                float scaleX = cellWidth / tW;
                float scaleY = cellHeight / tH;

                backSprite.setScale(scaleX, scaleY);
                backSprite.setPosition(posX, posY);

                frontSprite.setScale(scaleX, scaleY);
                frontSprite.setPosition(posX, posY);
            }

            window->draw(plot->get_backSprite());
            window->draw(plot->get_frontSprite());

            if (plot->getEntity()) {
                // ��� Barley
                Barley* barley = dynamic_cast<Barley*>(plot->getEntity());
                if (barley) {
                    float px = plot->get_frontSprite().getPosition().x;
                    float py = plot->get_frontSprite().getPosition().y;
                    barley->drawWaterLevel(*window, px, py);
                }
                // ��� Wheat
                Wheat* wheat = dynamic_cast<Wheat*>(plot->getEntity());
                if (wheat) {
                    float px = plot->get_frontSprite().getPosition().x;
                    float py = plot->get_frontSprite().getPosition().y;
                    wheat->drawWaterLevel(*window, px, py);
                }
            }
        }
    }
}

void Farm::drawFertiliserSprites(sf::RenderWindow* window) {
    sf::Vector2u windowSize = window->getSize();
    int plotsX = plots.size();
    int plotsY = plots[0].size();

    float cellWidth = windowSize.x / static_cast<float>(gridLength);
    float cellHeight = windowSize.y / static_cast<float>(gridLength);

    int startX = 2;
    int startY = 3;

    static std::map<std::string, sf::Texture> textureCache;

    for (int x = 0; x < plotsX; ++x) {
        for (int y = 0; y < plotsY; ++y) {
            Plot* plot = plots[x][y];
            std::string fertSpritePath = plot->getFertiliserSpriteOnPlot();
            if (!fertSpritePath.empty()) {
                if (textureCache.find(fertSpritePath) == textureCache.end()) {
                    textureCache[fertSpritePath] = sf::Texture();
                    textureCache[fertSpritePath].loadFromFile(fertSpritePath);
                }
                sf::Sprite fertSprite(textureCache[fertSpritePath]);
                // ������� ��� ������ ������
                fertSprite.setScale(cellWidth / fertSprite.getTexture()->getSize().x / 3,
                    cellHeight / fertSprite.getTexture()->getSize().y / 3);

                // ������� � ��� ���������, ���� ���� frontSprite
                float posX = (startX + x) * cellWidth;
                float posY = (startY + y) * cellHeight - cellHeight * 0.f;
                fertSprite.setPosition(posX, posY);

                window->draw(fertSprite);
            }
        }
    }
}

void Farm::createPlotOptionButtons(int plotX, int plotY, NotificationPanel* notifPanel) {
    plotOptionButtons.clear();
    float btnRadius = 70; // ������ ����� ������ �����
    float btnSize = 48; // ������ � ������ ������
    float centerX = (plotX + 2) * 80 + 40; // ����� ���������� ����� (� ������ �������� plotX+2)
    float centerY = (plotY + 3) * 80 + 40;

    std::vector<std::pair<std::string, std::function<void()>>> actions;

    if (plots[plotX][plotY]->isEmpty()) {
        actions = {
            {"sprites/ui/plant_wheat.png", [=]() {
                if (inventory->wheatSeedTake(1)) { plots[plotX][plotY]->placeEntity(new Wheat()); notifPanel->addMessage("�������� �������!"); }
                else notifPanel->addMessage("��� ����� �������!");
            }},
            {"sprites/ui/plant_barley.png", [=]() {
                if (inventory->barleySeedTake(1)) { plots[plotX][plotY]->placeEntity(new Barley()); notifPanel->addMessage("������� ������!"); }
                else notifPanel->addMessage("��� ����� ������!");
            }},
            {"sprites/ui/add_chicken.png", [=]() {
                if (inventory->ChickenTake(1)) { plots[plotX][plotY]->placeEntity(new Chicken()); notifPanel->addMessage("������ ���������!"); }
                else notifPanel->addMessage("��� ����� � ���������!");
            }},
            {"sprites/ui/add_sheep.png", [=]() {
                if (inventory->SheepTake(1)) { plots[plotX][plotY]->placeEntity(new Sheep()); notifPanel->addMessage("���� ���������!"); }
                else notifPanel->addMessage("��� ���� � ���������!");
            }},
        };
    }
    else if (plots[plotX][plotY]->get_isPlant()) {
        actions = {
            {"sprites/ui/watering_can.png", [=]() { plots[plotX][plotY]->water();}},
            {"sprites/fertilizer.png", [=]() {
                if (inventory->fertiliserTake(1)) { plots[plotX][plotY]->fertilise(inventory); notifPanel->addMessage("��������!"); }
                else notifPanel->addMessage("��� ���������!");
            }},
            {"sprites/ui/harvest.png", [=]() { plots[plotX][plotY]->harvest(inventory); notifPanel->addMessage("������ ������!"); }},
        };
    }
    else if (plots[plotX][plotY]->get_isAnimal()) {
        actions = {
            {"sprites/ui/water_bucket.png", [=]() { plots[plotX][plotY]->water(); notifPanel->addMessage("���� ����!"); }},
            {"sprites/ui/feed.png", [=]() {
                if (inventory->animalFeedTake(1)) { plots[plotX][plotY]->feed(inventory); notifPanel->addMessage("����������!"); }
                else notifPanel->addMessage("��� �����!");
            }},
            {"sprites/ui/animal_product.png", [=]() { plots[plotX][plotY]->harvest(inventory); notifPanel->addMessage("�������!"); }},
            {"sprites/ui/slaughter.png", [=]() { plots[plotX][plotY]->Slaughter(inventory); notifPanel->addMessage("������!"); }},
        };
    }

    size_t n = actions.size();
    float angleStep = 2 * 3.1415926535f / n;

    for (size_t i = 0; i < n; ++i) {
        float angle = i * angleStep - 3.1415926535f / 2; // ����� ������
        float bx = centerX + btnRadius * cos(angle) - btnSize / 2;
        float by = centerY + btnRadius * sin(angle) - btnSize / 2;
        plotOptionButtons.emplace_back(std::make_unique<Button>(actions[i].first, bx, by, btnSize, btnSize, actions[i].second));
    }
}

bool Farm::handlePlotOptionButtonsEvent(const sf::Event& event, const sf::Vector2f& mousePos) {
    bool clicked = false;
    for (auto& btn : plotOptionButtons)
        if (btn->handleEvent(event, mousePos))
            clicked = true;
    return clicked;
}

void Farm::drawPlotOptionButtons(sf::RenderWindow* window) {
    for (auto& btn : plotOptionButtons) btn->draw(*window);
}
