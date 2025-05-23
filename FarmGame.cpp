#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "headers/Farm.h"
#include "headers/GameTile.h"
#include "headers/menu.h"
#include "headers/MoneyPanel.h"
#include <Windows.h>
#include "../headers/MessagePanel.h"

enum MusicMenuState {
    MUSIC_MENU_CLOSED,
    MUSIC_MENU_OPEN
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int menuWidth = 800;
    int menuHeight = 800;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    int menuPosX = (desktop.width - menuWidth) / 2;
    int menuPosY = (desktop.height - menuHeight) / 2;

    sf::RenderWindow menuWindow(sf::VideoMode(menuWidth, menuHeight), "FarmVille!", sf::Style::Titlebar | sf::Style::Close);

    HWND menuHwnd = menuWindow.getSystemHandle();
    SetWindowPos(menuHwnd, HWND_TOP, menuPosX, menuPosY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

    if (!showMenu(menuWindow))
        return 0;

    menuWindow.close(); // Закрываем меню

    sf::RenderWindow window(sf::VideoMode(800, 800), "FarmVille!", sf::Style::Titlebar | sf::Style::Close);
    // Центрирование окна на экране
    int winWidth = 800;
    int winHeight = 800;
    int winPosX = (desktop.width - winWidth) / 2;
    int winPosY = (desktop.height - winHeight) / 2;
    HWND hwnd = window.getSystemHandle();
    SetWindowPos(hwnd, HWND_TOP, winPosX, winPosY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

    // Устанавливаем view на весь экран (чтобы контент занимал всё окно)
    sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
    window.setView(view);

    // --- Music Setup ---
    sf::Music music;
    if (!music.openFromFile("audio/menuMusic.ogg")) {
        std::cerr << "Не удалось загрузить музыку!" << std::endl;
    }
    else {
        music.setLoop(true);
        music.setVolume(60); // громкость по умолчанию
        music.play();
    }
    bool isMusicOn = true;
    // --- End Music Setup ---

    Farm farm = Farm();
    int showInv = -1;      // Флаг отображения инвентаря (-1 - скрыт, 1 - показан)
    int showShop = -1;     // Флаг отображения магазина
    int showHelp = -1;     // Флаг отображения справки
    sf::Vector2f relevantWindowSize(window.getSize());  // Актуальный размер окна
    sf::Vector2f mousePressPos;       // Позиция нажатия мыши
    sf::Vector2f selectedGametile;    // Выбранная клетка на поле
    MessagePanel messagePanel;

    sf::Font font;
    if (!font.loadFromFile("Silkscreen/CyrilicOld.ttf")) {
        std::cerr << "Не удалось загрузить шрифт для меню музыки!" << std::endl;
    }
    sf::RectangleShape musicMenuButton(sf::Vector2f(40, 40));
    musicMenuButton.setFillColor(sf::Color(180, 180, 220));
    musicMenuButton.setOutlineThickness(2);
    musicMenuButton.setOutlineColor(sf::Color::Black);
    musicMenuButton.setPosition(window.getSize().x - 50, 10);

    sf::Text musicOnText("Вкл/Выкл музыку", font, 18);
    musicOnText.setFillColor(sf::Color::Black);
    musicOnText.setPosition(window.getSize().x - 170, 70);

    sf::Text exitGameText("Выход из игры", font, 18);
    exitGameText.setFillColor(sf::Color::Black);
    exitGameText.setPosition(window.getSize().x - 170, 110);

    // Области кнопок (для обработки кликов)
    sf::FloatRect musicOnBtnRect(window.getSize().x - 170, 70, 160, 30);
    sf::FloatRect exitGameBtnRect(window.getSize().x - 170, 110, 160, 30);

    // Загрузка фонового изображения (делаем это один раз)
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("sprites/main.png")) {
        std::cerr << "Не удалось загрузить фон main.png!" << std::endl;
    }
    sf::Sprite background(backgroundTexture);
    float scaleX = window.getSize().x / static_cast<float>(backgroundTexture.getSize().x);
    float scaleY = window.getSize().y / static_cast<float>(backgroundTexture.getSize().y);
    background.setScale(scaleX, scaleY);

    sf::Text musicMenuText("♫", font, 24);
    musicMenuText.setFillColor(sf::Color::Black);
    musicMenuText.setPosition(window.getSize().x - 42, 11);

    MusicMenuState musicMenuState = MUSIC_MENU_CLOSED;
    sf::RectangleShape musicMenuPanel(sf::Vector2f(170, 120));
    musicMenuPanel.setFillColor(sf::Color(230, 230, 255, 240));
    musicMenuPanel.setOutlineThickness(2);
    musicMenuPanel.setOutlineColor(sf::Color(100, 100, 180));
    musicMenuPanel.setPosition(window.getSize().x - 180, 60);

    //sf::Text musicOnText("Вкл/Выкл музыку", font, 18);
    //musicOnText.setFillColor(sf::Color::Black);
    //musicOnText.setPosition(window.getSize().x - 170, 70);

   /* sf::Text exitGameText("Выход из игры", font, 18);
    exitGameText.setFillColor(sf::Color::Black);
    exitGameText.setPosition(window.getSize().x - 170, 110);*/

    // Области кнопок (для обработки кликов)
  /*  sf::FloatRect musicOnBtnRect(window.getSize().x - 170, 70, 160, 30);
    sf::FloatRect exitGameBtnRect(window.getSize().x - 170, 110, 160, 30);*/

    // Загрузка фонового изображения (делаем это один раз)
   /* sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("sprites/main.png")) {
        std::cerr << "Не удалось загрузить фон main.png!" << std::endl;
    }
    sf::Sprite background(backgroundTexture);
    float scaleX = window.getSize().x / static_cast<float>(backgroundTexture.getSize().x);
    float scaleY = window.getSize().y / static_cast<float>(backgroundTexture.getSize().y);
    background.setScale(scaleX, scaleY);*/

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized) {
                sf::View newView;
                newView.setSize(event.size.width, event.size.height);
                newView.setCenter(event.size.width / 2.f, event.size.height / 2.f);
                window.setView(newView);

                float scaleX = event.size.width / static_cast<float>(backgroundTexture.getSize().x);
                float scaleY = event.size.height / static_cast<float>(backgroundTexture.getSize().y);
                background.setScale(scaleX, scaleY);
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mousePosF = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                mousePressPos = mousePosF; // Используем только одну систему координат!

                // Проверка нажатия на меню музыки
                if (musicMenuButton.getGlobalBounds().contains(mousePosF)) {
                    musicMenuState = (musicMenuState == MUSIC_MENU_CLOSED) ? MUSIC_MENU_OPEN : MUSIC_MENU_CLOSED;
                }
                // Обработка кнопок в меню музыки
                if (musicMenuState == MUSIC_MENU_OPEN) {
                    if (musicOnBtnRect.contains(mousePosF)) {
                        // Вкл/Выкл музыку
                        if (isMusicOn) {
                            music.pause();
                            isMusicOn = false;
                        }
                        else {
                            music.play();
                            isMusicOn = true;
                        }
                    }
                    if (exitGameBtnRect.contains(mousePosF)) {
                        window.close();
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I)
            {
                // Открытие/закрытие инвентаря по клавише I
                showInv *= -1;
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::B) {
                // Открытие/закрытие магазина по клавише B
                showShop *= -1;
            }

            // Опции магазина (если он открыт)
            if (showShop == 1 && event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num1) {
                    // Покупка семян пшеницы (цена: 2)
                    if (farm.inventory->moneyTake(2) == true) {
                        farm.inventory->wheatSeedAdd(1);
                        messagePanel.addMessage("Успешно куплено 1 семя пшеницы");
                    }
                    else {
                        messagePanel.addMessage("Недостаточно денег для покупки семян пшеницы");
                    }
                }
                if (event.key.code == sf::Keyboard::Num2) {
                    // Покупка семян ячменя (цена: 3)
                    if (farm.inventory->moneyTake(3) == true) {
                        farm.inventory->barleySeedAdd(1);
                        messagePanel.addMessage("Успешно куплено 1 семя ячменя");
                    }
                    else {
                        messagePanel.addMessage("Недостаточно денег для покупки семян ячменя");
                    }
                }
                if (event.key.code == sf::Keyboard::Num3) {
                    // Покупка курицы (цена: 15)
                    if (farm.inventory->moneyTake(15) == true) {
                        farm.inventory->ChickenAdd(1);
                        messagePanel.addMessage("Успешно куплена 1 курица");
                    }
                    else {
                        messagePanel.addMessage("Недостаточно денег для покупки курицы");
                    }
                }
                if (event.key.code == sf::Keyboard::Num4) {
                    // Покупка овцы (цена: 20)
                    if (farm.inventory->moneyTake(20) == true) {
                        farm.inventory->SheepAdd(1);
                        messagePanel.addMessage("Успешно куплена 1 овца");
                    }
                    else {
                        messagePanel.addMessage("Недостаточно денег для покупки овцы");
                    }
                }
                if (event.key.code == sf::Keyboard::Num5) {
                    // Покупка корма для животных (цена: 1)
                    if (farm.inventory->moneyTake(1) == true) {
                        farm.inventory->animalFeedAdd(1);
                        messagePanel.addMessage("Успешно куплен 1 корм для животных");
                    }
                    else {
                        messagePanel.addMessage("Недостаточно денег для покупки корма");
                    }
                }
                if (event.key.code == sf::Keyboard::Num6) {
                    // Покупка удобрения (цена: 2)
                    if (farm.inventory->moneyTake(2) == true) {
                        farm.inventory->fertiliserAdd(1);
                        messagePanel.addMessage("Успешно куплено 1 удобрение");
                    }
                    else {
                        messagePanel.addMessage("Недостаточно денег для покупки удобрения");
                    }
                }
                if (event.key.code == sf::Keyboard::Num7) {
                    // Продажа всех товаров
                    if (farm.shop->sellGoods(farm.inventory) == true) {
                        messagePanel.addMessage("Успешно проданы все товары");
                    }
                    else {
                        messagePanel.addMessage("Ошибка при продаже товаров");
                    }
                }
            }

            // Действия на выбранной клетке (если магазин закрыт)
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1 && showShop == -1)
            {
                // Действие по клавише 1: посадка пшеницы или полив
                if (farm.selectedTileIsPlot(selectedGametile))
                {
                    if (farm.plots[(int)selectedGametile.x - 2][(int)selectedGametile.y - 3]->isEmpty() == true)
                    {
                        // Посадка пшеницы, если есть семена
                        if (farm.inventory->wheatSeedTake(1) == true) {
                            Wheat* newWheat = new Wheat;
                            farm.plots[(int)selectedGametile.x - 2][(int)selectedGametile.y - 3]->placeEntity(newWheat);
                        }
                        else {
                            messagePanel.addMessage("Нельзя посадить пшеницу: нет семян.");
                        }
                    }
                    else if (farm.plots[(int)selectedGametile.x - 2][(int)selectedGametile.y - 3]->isEmpty() == false)
                    {
                        // Полив растения/животного
                        farm.plots[(int)selectedGametile.x - 2][(int)selectedGametile.y - 3]->water();
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2 && showShop == -1)
            {
                // Действие по клавише 2: посадка ячменя, удобрение или кормление
                if (farm.selectedTileIsPlot(selectedGametile)) {
                    if (farm.plots[(int)selectedGametile.x - 2][(int)selectedGametile.y - 3]->isEmpty() == true) {
                        // Посадка ячменя, если есть семена
                        if (farm.inventory->barleySeedTake(1) == true) {
                            Barley* newBarley = new Barley;
                            farm.plots[(int)selectedGametile.x - 2][(int)selectedGametile.y - 3]->placeEntity(newBarley);
                        }
                        else {
                            messagePanel.addMessage("Нельзя посадить ячмень : нет семян");
                        }
                    }
                    else if (farm.plots[(int)selectedGametile.x - 2][(int)selectedGametile.y - 3]->get_isPlant() == true) {
                        // Удобрение растения, если есть удобрения
                        if (farm.inventory->fertiliserTake(1) == true) {
                            farm.plots[(int)selectedGametile.x - 2][(int)selectedGametile.y - 3]->fertilise(farm.inventory);
                        }
                        else {
                            messagePanel.addMessage("Нельзя удобрить: нет удобрений.");
                        }
                    }
                    else if (farm.plots[(int)selectedGametile.x - 2][(int)selectedGametile.y - 3]->get_isAnimal() == true) {
                        // Кормление животного, если есть корм
                        if (farm.inventory->animalFeedTake(1) == true) {
                            farm.plots[(int)selectedGametile.x - 2][(int)selectedGametile.y - 3]->feed(farm.inventory);
                        }
                        else {
                            messagePanel.addMessage("Нельзя покормить: нет корма.");
                        }
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3 && showShop == -1)
            {
                // Действие по клавише 3: сбор урожая или размещение курицы
                if (farm.selectedTileIsPlot(selectedGametile) && farm.plots[(int)selectedGametile.x - 2][(int)selectedGametile.y - 3]->isEmpty() == false)
                {
                    // Сбор урожая
                    farm.plots[(int)selectedGametile.x - 2][(int)selectedGametile.y - 3]->harvest(farm.inventory);
                }
                else if (farm.selectedTileIsPlot(selectedGametile) && farm.plots[(int)selectedGametile.x - 2][(int)selectedGametile.y - 3]->isEmpty() == true)
                {
                    // Размещение курицы, если она есть в инвентаре
                    if (farm.inventory->ChickenTake(1) == true) {
                        Chicken* newChicken = new Chicken;
                        farm.plots[(int)selectedGametile.x - 2][(int)selectedGametile.y - 3]->placeEntity(newChicken);
                    }
                    else {
                        messagePanel.addMessage("Нельзя разместить курицу: нет куриц в инвентаре");
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num4 && showShop == -1)
            {
                // Действие по клавише 4: забить животное или разместить овцу
                if (farm.selectedTileIsPlot(selectedGametile) && farm.plots[(int)selectedGametile.x - 2][(int)selectedGametile.y - 3]->get_isAnimal() == true) {
                    // Забой животного
                    farm.plots[(int)selectedGametile.x - 2][(int)selectedGametile.y - 3]->Slaughter(farm.inventory);
                }
                else if (farm.selectedTileIsPlot(selectedGametile) && farm.plots[(int)selectedGametile.x - 2][(int)selectedGametile.y - 3]->isEmpty() == true)
                {
                    // Размещение овцы, если она есть в инвентаре
                    if (farm.inventory->SheepTake(1) == true) {
                        Sheep* newSheep = new Sheep;
                        farm.plots[(int)selectedGametile.x - 2][(int)selectedGametile.y - 3]->placeEntity(newSheep);
                    }
                    else {
                        messagePanel.addMessage("Нельзя разместить овцу: нет овец в инвентаре");
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::H) {
                // Открытие/закрытие справки по клавише H
                showHelp *= -1;
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
            {
                // Пропуск времени по клавише P
                farm.passTime(&window);
            }

            // Сохранение данных инвентаря в файл (клавиша S)
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
            {
                if (farm.inventory->saveDataToFile("InventoryData.txt"))
                {
                    messagePanel.addMessage("Данные инвентаря успешно сохранены.");
                }
                else
                {
                    messagePanel.addMessage("Ошибка сохранения данных инвентаря.");
                }
            }

            // Загрузка данных инвентаря из файла (клавиша L)
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::L)
            {
                if (farm.inventory->loadDataFromFile("InventoryData.txt"))
                {
                    messagePanel.addMessage("Данные инвентаря успешно загружены.");
                }
                else
                {
                    messagePanel.addMessage("Ошибка загрузки данных инвентаря.");
                }
            }
        }

        // Получение позиции выбранной клетки на основе позиции мыши
        selectedGametile.x = (int)mousePressPos.x / 80;
        selectedGametile.y = (int)mousePressPos.y / 80;

        window.clear();

        // Отрисовка фона
        window.draw(background);

        MoneyPanel moneyPanel;

        if (!moneyPanel.loadResources()) {
            std::cerr << "Ошибка загрузки ресурсов MoneyPanel!" << std::endl;
        }
        moneyPanel.setPosition(610, 7); // Позиция на экране
        moneyPanel.setInventory(farm.inventory); // Начальное количество денег
        moneyPanel.draw(window);

        // --- Рисуем кнопку меню музыки ---
        window.draw(musicMenuButton);
        window.draw(musicMenuText);

        // --- Если меню музыки открыто, рисуем панель и кнопки ---
        if (musicMenuState == MUSIC_MENU_OPEN) {
            window.draw(musicMenuPanel);
            window.draw(musicOnText);
            window.draw(exitGameText);
            // Можно добавить визуальный фидбек для кнопок
            if (!isMusicOn) {
                sf::Text offText("Отключено", font, 14);
                offText.setFillColor(sf::Color::Red);
                offText.setPosition(window.getSize().x - 50, 70);
                window.draw(offText);
            }
        }

        // Отображение подсказки о справке
        farm.displayFarmText(&window, "Нажмите H для открытия справки!", 0, 0);

        // Отрисовка всех клеток фермы
        farm.drawPlots(&window);

        // Отображение опций для выбранной клетки
        if (farm.selectedTileIsPlot(selectedGametile))
        {
            farm.getPlotOptions(&window, (float)selectedGametile.x, (float)selectedGametile.y);
            farm.tiles[(int)selectedGametile.x][(int)selectedGametile.y]->drawSelectionBox(&window);
        }

        // Отображение инвентаря (если открыт)
        if (showInv == 1)
            farm.inventory->show(&window);

        // Отображение магазина (если открыт)
        if (showShop == 1)
            farm.shop->shopOpen(&window, farm.inventory->getMoney());

        // Отображение справки (если открыта)
        if (showHelp == 1) {
            farm.get_Help(&window);
        }

        messagePanel.draw(window);

        window.display();
    }
}