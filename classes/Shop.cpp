#include "../headers/Shop.h"

bool Shop::shopOpen(sf::RenderWindow* window, int money)
{
    shopIsOpen = true;
    constexpr int winW = 800, winH = 800;
    constexpr int shopW = 700;
    constexpr int shopH = 800;
    shop_pos_x = (winW - shopW) / 2;
    shop_pos_y = 0;

    std::string texture_filename = "sprites/Shop_background.png";
    if (!Backdrop_texture.loadFromFile(texture_filename))
    {
        std::cout << "ќшибка загрузки файла: " << texture_filename << std::endl;
        return false;
    }
    Backdrop_sprite.setTexture(Backdrop_texture);
    Backdrop_sprite.setPosition(sf::Vector2f(shop_pos_x, shop_pos_y));
    Backdrop_sprite.setScale(
        float(shopW) / Backdrop_texture.getSize().x,
        float(shopH) / Backdrop_texture.getSize().y
    );
    window->draw(Backdrop_sprite);

    // "ћј√ј«»Ќ" Ч слева сверху, смещено на 10px правее
    displayShopText(window, "ћј√ј«»Ќ", shop_pos_x + 80, shop_pos_y + 40, 48, sf::Color(30, 30, 30));
    displayShopText(window, "ƒеньги: ", shop_pos_x + shopW - 210, shop_pos_y + 54, 28, sf::Color(40, 40, 40));
    displayShopText(window, std::to_string(money), shop_pos_x + shopW - 110, shop_pos_y + 54, 28, sf::Color(40, 40, 40));

    // —писок товаров Ч $ выравнены по одной вертикали, смещено на 20px правее (было -150, стало -130)
    int itemStartY = shop_pos_y + 170;
    int itemStep = 80;
    int labelX = shop_pos_x + 80;
    int priceX = shop_pos_x + shopW - 130; // Ѕыло -150, теперь еще правее на 20px

    displayShopText(window, "1.  упить семена пшеницы", labelX, itemStartY + itemStep * 0, 36, sf::Color::Black);
    displayShopText(window, "$2", priceX, itemStartY + itemStep * 0, 36, sf::Color::Black);

    displayShopText(window, "2.  упить семена €чмен€", labelX, itemStartY + itemStep * 1, 36, sf::Color::Black);
    displayShopText(window, "$3", priceX, itemStartY + itemStep * 1, 36, sf::Color::Black);

    displayShopText(window, "3.  упить курицу", labelX, itemStartY + itemStep * 2, 36, sf::Color::Black);
    displayShopText(window, "$15", priceX, itemStartY + itemStep * 2, 36, sf::Color::Black);

    displayShopText(window, "4.  упить овцу", labelX, itemStartY + itemStep * 3, 36, sf::Color::Black);
    displayShopText(window, "$20", priceX, itemStartY + itemStep * 3, 36, sf::Color::Black);

    displayShopText(window, "5.  упить корм дл€ животных", labelX, itemStartY + itemStep * 4, 36, sf::Color::Black);
    displayShopText(window, "$1", priceX, itemStartY + itemStep * 4, 36, sf::Color::Black);

    displayShopText(window, "6.  упить удобрени€", labelX, itemStartY + itemStep * 5, 36, sf::Color::Black);
    displayShopText(window, "$2", priceX, itemStartY + itemStep * 5, 36, sf::Color::Black);

    displayShopText(window, "7. ѕродать товары", labelX, itemStartY + itemStep * 6, 36, sf::Color::Black);

    return true;
}

void Shop::set_shopIsOpen(bool _shopIsOpen)
{
    shopIsOpen = _shopIsOpen;
}

bool Shop::get_shopIsOpen()
{
    return shopIsOpen;
}

void Shop::displayShopText(sf::RenderWindow* window, std::string display_string, int x, int y, int size, sf::Color color)
{
    static sf::Font font;
    static bool loaded = false;
    if (!loaded) {
        font.loadFromFile("Silkscreen/CyrilicOld.ttf");
        loaded = true;
    }

    sf::Text text;
    text.setFont(font);
    text.setString(display_string);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(x, y);
    window->draw(text);
}

void Shop::displayShopText(sf::RenderWindow* window, std::string display_string, int x, int y)
{
    displayShopText(window, display_string, x, y, 22, sf::Color::Black);
}

Shop::Shop()
{
    shopIsOpen = false;
    shop_pos_x = 0;
    shop_pos_y = 0;
}

bool Shop::sellGoods(Inventory* Inventory)
{
    int Eggs = Inventory->getEggs();
    Inventory->eggsTake(Eggs);
    Inventory->moneyAdd(Eggs * 5);

    int BarleyGrain = Inventory->getBarleyGrain();
    Inventory->barleyGrainTake(BarleyGrain);
    Inventory->moneyAdd(BarleyGrain * 15);

    int WheatGrain = Inventory->getWheatGrain();
    Inventory->wheatGrainTake(WheatGrain);
    Inventory->moneyAdd(WheatGrain * 10);

    int Wool = Inventory->getWool();
    Inventory->woolTake(Wool);
    Inventory->moneyAdd(Wool * 10);

    int Meat = Inventory->getMeat();
    Inventory->meatTake(Meat);
    Inventory->moneyAdd(Meat * 5);

    return true;
}