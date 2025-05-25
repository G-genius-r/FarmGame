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
#include "headers/MusicMenu.h"
#include "headers/NotificationPanel.h"

// Глобальные переменные для хранения выбранной клетки
int selectedPlotX = -1;
int selectedPlotY = -1;

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

    bool isMusicOn = true;
    if (!showMenu(menuWindow, isMusicOn))
        return 0;

    menuWindow.close();

    sf::RenderWindow window(sf::VideoMode(800, 800), "FarmVille!", sf::Style::Titlebar | sf::Style::Close);
    int winWidth = 800;
    int winHeight = 800;
    int winPosX = (desktop.width - winWidth) / 2;
    int winPosY = (desktop.height - winHeight) / 2;
    HWND hwnd = window.getSystemHandle();
    SetWindowPos(hwnd, HWND_TOP, winPosX, winPosY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

    sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
    window.setView(view);

    sf::Music music;
    if (!music.openFromFile("audio/menuMusic.ogg")) {
        std::cerr << "Не удалось загрузить музыку!" << std::endl;
    }
    else {
        music.setLoop(true);
        music.setVolume(60);
        if (isMusicOn)
            music.play();
        else
            music.pause();
    }

    MusicMenu musicMenu(window);

    Farm farm;
    int showInv = -1;
    int showShop = -1;
    int showHelp = -1;
    sf::Vector2f mousePressPos;
    NotificationPanel notifPanel;

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("sprites/main.png")) {
        std::cerr << "Не удалось загрузить фон main.png!" << std::endl;
    }
    sf::Sprite background(backgroundTexture);
    float scaleX = window.getSize().x / static_cast<float>(backgroundTexture.getSize().x);
    float scaleY = window.getSize().y / static_cast<float>(backgroundTexture.getSize().y);
    background.setScale(scaleX, scaleY);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            musicMenu.handleEvent(event, window, music, isMusicOn);

            MusicMenu::Action musicAction = musicMenu.pollAction();
            if (musicAction == MusicMenu::MAIN_MENU) {
                music.pause();
                bool startGame = showMenu(window, isMusicOn);
                if (!startGame) {
                    window.close();
                    break;
                }
                if (isMusicOn)
                    music.play();
                else
                    music.pause();
                continue;
            }
            if (musicAction == MusicMenu::EXIT_GAME) {
                window.close();
                break;
            }
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

            if (musicMenu.isOpen()) continue;

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                if (showInv == 1) showInv = -1;
                if (showShop == 1) showShop = -1;
                if (showHelp == 1) showHelp = -1;
                continue;
            }

            // Если клик по UI-панели (инвентарь, магазин, справка, меню музыки)
            if ((event.type == sf::Event::MouseButtonPressed) &&
                (showInv == 1 || showShop == 1 || showHelp == 1 || musicMenu.isOpen())) {
                if (showInv == 1) showInv = -1;
                if (showShop == 1) showShop = -1;
                if (showHelp == 1) showHelp = -1;
                if (musicMenu.isOpen()) musicMenu.close();
                continue;
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mousePosF = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                bool buttonClicked = farm.handlePlotOptionButtonsEvent(event, mousePosF);

                if (!buttonClicked) {
                    float tileWidth = window.getSize().x / static_cast<float>(farm.getGridLength());
                    float tileHeight = window.getSize().y / static_cast<float>(farm.getGridLength());
                    int tileX = static_cast<int>(mousePosF.x / tileWidth);
                    int tileY = static_cast<int>(mousePosF.y / tileHeight);

                    // Проверяем, клик по участку или нет
                    if (!farm.selectedTileIsPlot(sf::Vector2f(tileX, tileY))) {
                        farm.clearPlotOptionButtons();
                        selectedPlotX = -1;
                        selectedPlotY = -1;
                    }
                    else {
                        // Если выбран новый участок - обновить выделение и перегенерировать кнопки
                        if (selectedPlotX != tileX || selectedPlotY != tileY) {
                            selectedPlotX = tileX;
                            selectedPlotY = tileY;
                        }
                        mousePressPos = mousePosF;
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I) {
                showInv *= -1;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::B) {
                showShop *= -1;
            }

            // Опции магазина (если он открыт)
            if (showShop == 1 && event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num1) {
                    if (farm.inventory->moneyTake(2)) {
                        farm.inventory->wheatSeedAdd(1);
                        notifPanel.addMessage("Успешно куплено 1 семя пшеницы");
                    }
                    else {
                        notifPanel.addMessage("Недостаточно денег для покупки семян пшеницы");
                    }
                }
                if (event.key.code == sf::Keyboard::Num2) {
                    if (farm.inventory->moneyTake(3)) {
                        farm.inventory->barleySeedAdd(1);
                        notifPanel.addMessage("Успешно куплено 1 семя ячменя");
                    }
                    else {
                        notifPanel.addMessage("Недостаточно денег для покупки семян ячменя");
                    }
                }
                if (event.key.code == sf::Keyboard::Num3) {
                    if (farm.inventory->moneyTake(15)) {
                        farm.inventory->ChickenAdd(1);
                        notifPanel.addMessage("Успешно куплена 1 курица");
                    }
                    else {
                        notifPanel.addMessage("Недостаточно денег для покупки курицы");
                    }
                }
                if (event.key.code == sf::Keyboard::Num4) {
                    if (farm.inventory->moneyTake(20)) {
                        farm.inventory->SheepAdd(1);
                        notifPanel.addMessage("Успешно куплена 1 овца");
                    }
                    else {
                        notifPanel.addMessage("Недостаточно денег для покупки овцы");
                    }
                }
                if (event.key.code == sf::Keyboard::Num5) {
                    if (farm.inventory->moneyTake(1)) {
                        farm.inventory->animalFeedAdd(1);
                        notifPanel.addMessage("Успешно куплен 1 корм для животных");
                    }
                    else {
                        notifPanel.addMessage("Недостаточно денег для покупки корма");
                    }
                }
                if (event.key.code == sf::Keyboard::Num6) {
                    if (farm.inventory->moneyTake(2)) {
                        farm.inventory->fertiliserAdd(1);
                        notifPanel.addMessage("Успешно куплено 1 удобрение");
                    }
                    else {
                        notifPanel.addMessage("Недостаточно денег для покупки удобрения");
                    }
                }
                if (event.key.code == sf::Keyboard::Num7) {
                    if (farm.shop->sellGoods(farm.inventory)) {
                        notifPanel.addMessage("Успешно проданы все товары");
                    }
                    else {
                        notifPanel.addMessage("Ошибка при продаже товаров");
                    }
                }
            }

            // Действия на выбранной клетке (если магазин закрыт)
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1 && showShop == -1 && selectedPlotX != -1 && selectedPlotY != -1)
            {
                if (farm.selectedTileIsPlot(sf::Vector2f(selectedPlotX, selectedPlotY)))
                {
                    int px = selectedPlotX - 2, py = selectedPlotY - 3;
                    if (farm.plots[px][py]->isEmpty())
                    {
                        if (farm.inventory->wheatSeedTake(1)) {
                            Wheat* newWheat = new Wheat;
                            farm.plots[px][py]->placeEntity(newWheat);
                        }
                        else {
                            notifPanel.addMessage("Нельзя посадить пшеницу: нет семян.");
                        }
                    }
                    else
                    {
                        farm.plots[px][py]->water();
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2 && showShop == -1 && selectedPlotX != -1 && selectedPlotY != -1)
            {
                if (farm.selectedTileIsPlot(sf::Vector2f(selectedPlotX, selectedPlotY))) {
                    int px = selectedPlotX - 2, py = selectedPlotY - 3;
                    if (farm.plots[px][py]->isEmpty()) {
                        if (farm.inventory->barleySeedTake(1)) {
                            Barley* newBarley = new Barley;
                            farm.plots[px][py]->placeEntity(newBarley);
                        }
                        else {
                            notifPanel.addMessage("Нельзя посадить ячмень : нет семян");
                        }
                    }
                    else if (farm.plots[px][py]->get_isPlant()) {
                        if (farm.inventory->fertiliserTake(1)) {
                            farm.plots[px][py]->fertilise(farm.inventory);
                        }
                        else {
                            notifPanel.addMessage("Нельзя удобрить: нет удобрений.");
                        }
                    }
                    else if (farm.plots[px][py]->get_isAnimal()) {
                        if (farm.inventory->animalFeedTake(1)) {
                            farm.plots[px][py]->feed(farm.inventory);
                        }
                        else {
                            notifPanel.addMessage("Нельзя покормить: нет корма.");
                        }
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3 && showShop == -1 && selectedPlotX != -1 && selectedPlotY != -1)
            {
                if (farm.selectedTileIsPlot(sf::Vector2f(selectedPlotX, selectedPlotY)))
                {
                    int px = selectedPlotX - 2, py = selectedPlotY - 3;
                    if (!farm.plots[px][py]->isEmpty())
                    {
                        farm.plots[px][py]->harvest(farm.inventory);
                    }
                    else
                    {
                        if (farm.inventory->ChickenTake(1)) {
                            Chicken* newChicken = new Chicken;
                            farm.plots[px][py]->placeEntity(newChicken);
                        }
                        else {
                            notifPanel.addMessage("Нельзя разместить курицу: нет куриц в инвентаре");
                        }
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num4 && showShop == -1 && selectedPlotX != -1 && selectedPlotY != -1)
            {
                if (farm.selectedTileIsPlot(sf::Vector2f(selectedPlotX, selectedPlotY))) {
                    int px = selectedPlotX - 2, py = selectedPlotY - 3;
                    if (farm.plots[px][py]->get_isAnimal()) {
                        farm.plots[px][py]->Slaughter(farm.inventory);
                    }
                    else
                    {
                        if (farm.inventory->SheepTake(1)) {
                            Sheep* newSheep = new Sheep;
                            farm.plots[px][py]->placeEntity(newSheep);
                        }
                        else {
                            notifPanel.addMessage("Нельзя разместить овцу: нет овец в инвентаре");
                        }
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
                farm.passTime(&window);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::H) {
                showHelp *= -1;
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
            {
                if (farm.inventory->saveDataToFile("InventoryData.txt"))
                    notifPanel.addMessage("Данные инвентаря успешно сохранены.");
                else
                    notifPanel.addMessage("Ошибка сохранения данных инвентаря.");
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::L)
            {
                if (farm.inventory->loadDataFromFile("InventoryData.txt"))
                    notifPanel.addMessage("Данные инвентаря успешно загружены.");
                else
                    notifPanel.addMessage("Ошибка загрузки данных инвентаря.");
            }
        }

        // === ВЫЗЫВАТЬ createPlotOptionButtons КАЖДЫЙ КАДР ===
        if (selectedPlotX != -1 && selectedPlotY != -1 && farm.selectedTileIsPlot(sf::Vector2f(selectedPlotX, selectedPlotY))) {
            int px = selectedPlotX - 2;
            int py = selectedPlotY - 3;
            farm.createPlotOptionButtons(px, py, &notifPanel);
        }

        window.clear();
        window.draw(background);
        notifPanel.draw(window);

        MoneyPanel moneyPanel;
        if (!moneyPanel.loadResources()) {
            std::cerr << "Ошибка загрузки ресурсов MoneyPanel!" << std::endl;
        }
        moneyPanel.setPosition(610, 7);
        moneyPanel.setInventory(farm.inventory);
        moneyPanel.draw(window);

        farm.drawDayCounter(&window);
        farm.displayFarmText(&window, "Нажмите H для открытия справки!", 0, 0);

        farm.drawPlots(&window);
        farm.drawFertiliserSprites(&window);
        farm.drawPlotOptionButtons(&window);

        // Подсветка выбранного участка и кнопки вокруг него
        if (selectedPlotX != -1 && selectedPlotY != -1 && farm.selectedTileIsPlot(sf::Vector2f(selectedPlotX, selectedPlotY))) {
            farm.tiles[selectedPlotX][selectedPlotY]->drawSelectionBox(&window);
        }

        musicMenu.draw(window, isMusicOn);

        if (showInv == 1)
            farm.inventory->show(&window);
        if (showShop == 1)
            farm.shop->shopOpen(&window, farm.inventory->getMoney());
        if (showHelp == 1)
            farm.get_Help(&window);

        window.display();
    }
}