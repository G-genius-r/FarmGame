#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "../headers/Farm.h"
#include <vector>

// ����������� ������ Farm
Farm::Farm()
{
    gridLength = 10; // ��������� ������� �����
    dayCounter = 0;  // ������������� �������� ����
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
            Plot* plot = new Plot("sprites/Transparent.png", 32 * (start.x + x), 32 * (start.y + y));
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
            row.push_back(new GameTile("sprites/Transparent.png", 32 * i, 32 * j));
        }
        tiles.push_back(row);
    }
    std::cout << "������� ������ �������" << std::endl;
}

// ������� �� ��������� ����
void Farm::passTime(sf::RenderWindow* window)
{
    dayCounter++;
    std::cout << "�� ����� ������ ���� " << dayCounter << std::endl;

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
    sf::RectangleShape dayScreen;
    dayScreen.setFillColor(sf::Color::White);
    dayScreen.setSize(sf::Vector2f(350, 350));
    window->draw(dayScreen);
    displayFarmText(window, "����: ", 140, 150);
    displayFarmText(window, std::to_string(dayCounter), 175, 150);
    window->display();
    pause(2); // ����� 2 �������
}

// ����� � ����
void Farm::pause(int num_seconds)
{
    sf::Clock clock;
    while (clock.getElapsedTime().asSeconds() < num_seconds);
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
    Help_sprite.setPosition(help_x, help_y);
    window->draw(Help_sprite);

    // ����� ������
    std::vector<sf::String> helpText = {
    L"���� ������",
    L"������� 'B' ��� �������� ��������",
    L"������� 'I' ��� �������� ���������",
    L"������� 'P' ��� �������� �� ��������� ����",
    L"�������� ����� �������� ������ ����,",
    L"�������� ������ ���� ��� �� �����.",
    L"�������� ����� ����� � ������� ���������.",
    L"��� ����� ��� ��� ������",
    L"����������� ����� '�������'.",
    L"���� �������� ��� ��������",
    L"�� �������� ���� ��� ��� - ��� ��������.",
    L"���� ����� 10 ����, ���� - 15 ����.",
    L"����� � ����������!"
    };

    // ��������� ������ ������
    for (size_t i = 0; i < helpText.size(); i++)
    {
        displayFarmText(window, helpText[i], help_x + 25, help_y + 20 + i * 20);
    }

    return true;
}

// ����������� ����� ��� �������
void Farm::getPlotOptions(sf::RenderWindow* window, int pos_x, int pos_y)
{
    pos_x -= 2;
    pos_y -= 3;

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

// ����������� ������ �� �����
void Farm::displayFarmText(sf::RenderWindow* window, std::string text, int x, int y)
{
    sf::Font font;
    if (!font.loadFromFile("Silkscreen/arialmt.ttf"))
    {
        std::cout << "������ �������� ������" << std::endl;
        return;
    }

    sf::Text sfText;
    sfText.setFont(font);
    sfText.setString(text);
    sfText.setCharacterSize(10);
    sfText.setFillColor(sf::Color::Black);
    sfText.setPosition(x, y);
    window->draw(sfText);
}

// ��������� ���� ��������
void Farm::drawPlots(sf::RenderWindow* window)
{
    for (const auto& row : plots)
    {
        for (const auto& plot : row)
        {
            window->draw(plot->get_backSprite());
            window->draw(plot->get_frontSprite());
        }
    }
}