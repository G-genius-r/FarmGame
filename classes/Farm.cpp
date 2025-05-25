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

// Конструктор класса Farm
Farm::Farm()
{
    gridLength = 10; // Установка размера сетки
    dayCounter = 1;  // Инициализация счетчика дней
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
            Plot* plot = new Plot("sprites/Transparent.png", 80 * (start.x + x), 80 * (start.y + y));
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
            row.push_back(new GameTile("sprites/Transparent.png", 80 * i, 80 * j));
        }
        tiles.push_back(row);
    }
    std::cout << "Фоновые клетки созданы" << std::endl;
}

// Переход на следующий день
void Farm::passTime(sf::RenderWindow* window)
{
    dayCounter++;

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
    sf::Vector2u windowSize = window->getSize();

    sf::RectangleShape dayScreen;
    dayScreen.setFillColor(sf::Color::White);
    dayScreen.setSize(sf::Vector2f(windowSize.x, windowSize.y));
    window->draw(dayScreen);

    // Формируем строку "День: N"
    std::string dayText = "День: " + std::to_string(dayCounter);

    // Получаем ширину и высоту текста (предполагается, что displayFarmText возвращает размер текста)
    sf::Font font;
    font.loadFromFile("Silkscreen/CyrilicOld.ttf"); 
    sf::Text text(dayText, font, 48); 
    text.setFillColor(sf::Color::Black);

    // Центрируем текст по окну
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

    window->draw(text);

    window->display();
    pause(2); // Пауза 2 секунды
}

// Пауза в игре
void Farm::pause(int num_seconds)
{
    sf::Clock clock;
    while (clock.getElapsedTime().asSeconds() < num_seconds);
}

// отрисовка счетчика дней
void Farm::drawDayCounter(sf::RenderWindow* window)
{
    sf::Font font;
    if (!font.loadFromFile("Silkscreen/CyrilicOld.ttf"))
    {
        std::cout << "Ошибка загрузки шрифта" << std::endl;
        return;
    }

    std::string dayText = "День: " + std::to_string(dayCounter);

    sf::Text text(dayText, font, 32);
    text.setFillColor(sf::Color(220, 185, 138));

    // Обводка
    text.setOutlineColor(sf::Color::White); // желтая обводка
    text.setOutlineThickness(3.f); // толщина обводки

    sf::Vector2u windowSize = window->getSize();
    sf::FloatRect textRect = text.getLocalBounds();

    float rightMargin = 20.f;
    float posX = windowSize.x - textRect.width - rightMargin;
    float posY = 70.f;

    text.setPosition(posX, posY);

    window->draw(text);
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
    float scaleX = window->getSize().x / static_cast<float>(Help_texture.getSize().x);
    float scaleY = window->getSize().y / static_cast<float>(Help_texture.getSize().y);
    Help_sprite.setScale(scaleX, scaleY);
    window->draw(Help_sprite);

    // Текст помощи
    std::vector<sf::String> helpText = {
    "МЕНЮ ПОМОЩИ",
    "Нажмите 'B' для открытия магазина",
    "Нажмите 'I' для открытия инвентаря",
    "Нажмите 'P' для перехода на следующий день",
    "Растения нужно поливать каждый день,",
    "удобрять только один раз за жизнь.",
    "Животных нужно поить и кормить ежедневно.",
    "Для сбора яиц или шерсти",
    "используйте опцию 'Собрать'.",
    "Если растение или животное",
    "не получает воды или еды - оно погибнет.",
    "Куры живут 10 дней, овцы - 15 дней.",
    "Удачи в фермерстве!"
    };

    // Отрисовка текста помощи
    for (size_t i = 0; i < helpText.size(); i++)
    {
        displayFarmText(window, helpText[i], help_x + 25, help_y + 20 + i * 20);
    }

    return true;
}

// Отображение опций для участка
void Farm::getPlotOptions(sf::RenderWindow* window, float pos_x, float pos_y)
{
    pos_x -= 1.8;
    pos_y -= 2.3;

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

void Farm::clearPlotOptionButtons() {
    plotOptionButtons.clear();
}

int Farm::getGridLength() const {
    return gridLength;
}

// Отображение текста на ферме
void Farm::displayFarmText(sf::RenderWindow* window, std::string text, int x, int y)
{
    sf::Font font;
    if (!font.loadFromFile("Silkscreen/CyrilicOld.ttf"))
    {
        std::cout << "Ошибка загрузки шрифта" << std::endl;
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
    sfText.setOutlineColor(sf::Color(220, 185, 138)); // желтая обводка
    sfText.setOutlineThickness(3.f);
    sfText.setPosition(posX, posY);
    window->draw(sfText);
}

// Отрисовка всех участков
void Farm::drawPlots(sf::RenderWindow* window)
{
    sf::Vector2u windowSize = window->getSize();
    int plotsX = plots.size();
    int plotsY = plots[0].size();

    // Размер одной клетки (участка) на экране
    float cellWidth = windowSize.x / static_cast<float>(gridLength);
    float cellHeight = windowSize.y / static_cast<float>(gridLength);

    // Начальные индексы участков (например, 2,3 как в setPlots)
    int startX = 2;
    int startY = 3;

    for (int x = 0; x < plotsX; ++x)
    {
        for (int y = 0; y < plotsY; ++y)
        {
            Plot* plot = plots[x][y];
            // Получаем спрайты
            sf::Sprite backSprite = plot->get_backSprite();
            sf::Sprite frontSprite = plot->get_frontSprite();

            // Вычисляем позицию для этого участка
            float posX = (startX + x) * cellWidth;
            float posY = (startY + y) * cellHeight;

            // Масштабируем спрайты под размер клетки (участка)
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
                // Для Barley
                Barley* barley = dynamic_cast<Barley*>(plot->getEntity());
                if (barley) {
                    float px = plot->get_frontSprite().getPosition().x;
                    float py = plot->get_frontSprite().getPosition().y;
                    barley->drawWaterLevel(*window, px, py);
                }
                // Для Wheat
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
                // Масштаб под размер клетки
                fertSprite.setScale(cellWidth / fertSprite.getTexture()->getSize().x / 3,
                    cellHeight / fertSprite.getTexture()->getSize().y / 3);

                // Позиция — над растением, чуть выше frontSprite
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
    float btnRadius = 70; // радиус круга вокруг тайла
    float btnSize = 48; // ширина и высота кнопки
    float centerX = (plotX + 2) * 80 + 40; // центр выбранного тайла (с учётом смещения plotX+2)
    float centerY = (plotY + 3) * 80 + 40;

    std::vector<std::pair<std::string, std::function<void()>>> actions;

    if (plots[plotX][plotY]->isEmpty()) {
        actions = {
            {"sprites/ui/plant_wheat.png", [=]() {
                if (inventory->wheatSeedTake(1)) { plots[plotX][plotY]->placeEntity(new Wheat()); notifPanel->addMessage("Посажена пшеница!"); }
                else notifPanel->addMessage("Нет семян пшеницы!");
            }},
            {"sprites/ui/plant_barley.png", [=]() {
                if (inventory->barleySeedTake(1)) { plots[plotX][plotY]->placeEntity(new Barley()); notifPanel->addMessage("Посажен ячмень!"); }
                else notifPanel->addMessage("Нет семян ячменя!");
            }},
            {"sprites/ui/add_chicken.png", [=]() {
                if (inventory->ChickenTake(1)) { plots[plotX][plotY]->placeEntity(new Chicken()); notifPanel->addMessage("Курица размещена!"); }
                else notifPanel->addMessage("Нет куриц в инвентаре!");
            }},
            {"sprites/ui/add_sheep.png", [=]() {
                if (inventory->SheepTake(1)) { plots[plotX][plotY]->placeEntity(new Sheep()); notifPanel->addMessage("Овца размещена!"); }
                else notifPanel->addMessage("Нет овец в инвентаре!");
            }},
        };
    }
    else if (plots[plotX][plotY]->get_isPlant()) {
        actions = {
            {"sprites/ui/watering_can.png", [=]() { plots[plotX][plotY]->water();}},
            {"sprites/fertilizer.png", [=]() {
                if (inventory->fertiliserTake(1)) { plots[plotX][plotY]->fertilise(inventory); notifPanel->addMessage("Удобрено!"); }
                else notifPanel->addMessage("Нет удобрений!");
            }},
            {"sprites/ui/harvest.png", [=]() { plots[plotX][plotY]->harvest(inventory); notifPanel->addMessage("Урожай собран!"); }},
        };
    }
    else if (plots[plotX][plotY]->get_isAnimal()) {
        actions = {
            {"sprites/ui/water_bucket.png", [=]() { plots[plotX][plotY]->water(); notifPanel->addMessage("Дано воды!"); }},
            {"sprites/ui/feed.png", [=]() {
                if (inventory->animalFeedTake(1)) { plots[plotX][plotY]->feed(inventory); notifPanel->addMessage("Покормлено!"); }
                else notifPanel->addMessage("Нет корма!");
            }},
            {"sprites/ui/animal_product.png", [=]() { plots[plotX][plotY]->harvest(inventory); notifPanel->addMessage("Собрано!"); }},
            {"sprites/ui/slaughter.png", [=]() { plots[plotX][plotY]->Slaughter(inventory); notifPanel->addMessage("Забито!"); }},
        };
    }

    size_t n = actions.size();
    float angleStep = 2 * 3.1415926535f / n;

    for (size_t i = 0; i < n; ++i) {
        float angle = i * angleStep - 3.1415926535f / 2; // старт сверху
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
