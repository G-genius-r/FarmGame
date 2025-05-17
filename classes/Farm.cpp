#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "../headers/Farm.h"
#include <vector>

// Конструктор класса Farm
Farm::Farm()
{
    gridLength = 10; // Установка размера сетки
    dayCounter = 0;  // Инициализация счетчика дней
    setBackTiles();  // Создание фоновых клеток
    setPlots();      // Создание участков земли
    shop = new Shop(); // Инициализация магазина
    inventory = new Inventory(); // Инициализация инвентаря
    help_x = 20;     // Позиция меню помощи по X
    help_y = 0;      // Позиция меню помощи по Y
}

// Создание участков земли
void Farm::setPlots()
{
    plots.clear(); // Очистка существующих участков
    sf::Vector2f start(2, 3); // Начальная координата участков
    sf::Vector2f end(7, 6);   // Конечная координата участков

    // Создание сетки участков
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

// Создание фоновых клеток
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
    std::cout << "Фоновые клетки созданы" << std::endl;
}

// Переход на следующий день
void Farm::passTime(sf::RenderWindow* window)
{
    dayCounter++;
    std::cout << "На ферме теперь день " << dayCounter << std::endl;

    // Обновление всех участков
    for (auto& row : plots)
    {
        for (auto& plot : row)
        {
            if (!plot->isEmpty() && !plot->checkDeath())
            {
                plot->growEntity(); // Рост растения/животного
                plot->updateSprite();
            }
        }
    }

    // Анимация перехода дня
    sf::RectangleShape dayScreen;
    dayScreen.setFillColor(sf::Color::White);
    dayScreen.setSize(sf::Vector2f(350, 350));
    window->draw(dayScreen);
    displayFarmText(window, "День: ", 140, 150);
    displayFarmText(window, std::to_string(dayCounter), 175, 150);
    window->display();
    pause(2); // Пауза 2 секунды
}

// Пауза в игре
void Farm::pause(int num_seconds)
{
    sf::Clock clock;
    while (clock.getElapsedTime().asSeconds() < num_seconds);
}

// Изменение фонового спрайта
bool Farm::changeBackSprite(int x, int y, std::string textureFilename)
{
    return tiles[y][x]->setUpBackSprite(textureFilename);
}

// Меню помощи
bool Farm::get_Help(sf::RenderWindow* window)
{
    if (!Help_texture.loadFromFile("sprites/Shop_background.png"))
    {
        std::cout << "Ошибка загрузки текстуры помощи" << std::endl;
        return false;
    }

    Help_sprite.setTexture(Help_texture);
    Help_sprite.setPosition(help_x, help_y);
    window->draw(Help_sprite);

    // Текст помощи
    std::vector<sf::String> helpText = {
    L"МЕНЮ ПОМОЩИ",
    L"Нажмите 'B' для открытия магазина",
    L"Нажмите 'I' для открытия инвентаря",
    L"Нажмите 'P' для перехода на следующий день",
    L"Растения нужно поливать каждый день,",
    L"удобрять только один раз за жизнь.",
    L"Животных нужно поить и кормить ежедневно.",
    L"Для сбора яиц или шерсти",
    L"используйте опцию 'Собрать'.",
    L"Если растение или животное",
    L"не получает воды или еды - оно погибнет.",
    L"Куры живут 10 дней, овцы - 15 дней.",
    L"Удачи в фермерстве!"
    };

    // Отрисовка текста помощи
    for (size_t i = 0; i < helpText.size(); i++)
    {
        displayFarmText(window, helpText[i], help_x + 25, help_y + 20 + i * 20);
    }

    return true;
}

// Отображение опций для участка
void Farm::getPlotOptions(sf::RenderWindow* window, int pos_x, int pos_y)
{
    pos_x -= 2;
    pos_y -= 3;

    if (plots[pos_x][pos_y]->isEmpty())
    {
        // Опции для пустого участка
        std::vector<std::string> options = {
            "Этот участок пуст.",
            "1 - Посадить пшеницу (семена пшеницы)",
            "2 - Посадить ячмень (семена ячменя)",
            "3 - Посадить курицу (требуется курица)",
            "4 - Посадить овцу (требуется овца)"
        };
        for (size_t i = 0; i < options.size(); i++)
        {
            displayFarmText(window, options[i], pos_x * 32, pos_y * 32 + i * 15);
        }
    }
    else if (plots[pos_x][pos_y]->get_isAnimal())
    {
        // Опции для животных
        std::vector<std::string> options = {
            "1 - Дать воду",
            "2 - Покормить",
            "3 - Собрать (яйца/шерсть)",
            "4 - Забить"
        };
        for (size_t i = 0; i < options.size(); i++)
        {
            displayFarmText(window, options[i], pos_x * 32, pos_y * 32 + i * 15);
        }
    }
    else if (plots[pos_x][pos_y]->get_isPlant())
    {
        // Опции для растений
        std::vector<std::string> options = {
            "1 - Полить",
            "2 - Удобрить",
            "3 - Собрать урожай"
        };
        for (size_t i = 0; i < options.size(); i++)
        {
            displayFarmText(window, options[i], pos_x * 32, pos_y * 32 + i * 15);
        }
    }
}

// Проверка, является ли клетка участком
bool Farm::selectedTileIsPlot(sf::Vector2f selectedGametile)
{
    int tile_x = selectedGametile.x;
    int tile_y = selectedGametile.y;
    return (tile_x >= 2 && tile_x <= 7 && tile_y >= 3 && tile_y <= 6);
}

// Отображение текста на ферме
void Farm::displayFarmText(sf::RenderWindow* window, std::string text, int x, int y)
{
    sf::Font font;
    if (!font.loadFromFile("Silkscreen/arialmt.ttf"))
    {
        std::cout << "Ошибка загрузки шрифта" << std::endl;
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

// Отрисовка всех участков
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