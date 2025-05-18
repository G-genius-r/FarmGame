#include "../headers/GameTile.h"

#define GAMETILE_DIM 32

GameTile::GameTile() {
    pos = sf::Vector2f(0, 0);
    if (!setUpBackSprite("")) {
        std::cout << "не удалось установить фоновый спрайт в конструкторе GameTile" << std::endl;
        return;
    }
    if (!setUpFrontSprite("sprites/Transparent.png")) {
        std::cout << "не удалось установить передний спрайт в конструкторе GameTile" << std::endl;
        return;
    }
}

GameTile::GameTile(std::string backTextureFilename, float pos_x, float pos_y)
{
    pos = sf::Vector2f(pos_x, pos_y);
    if (!setUpBackSprite(backTextureFilename)) {
        std::cout << "не удалось установить фоновый спрайт в конструкторе GameTile" << std::endl;
        return;
    }
    if (!setUpFrontSprite("sprites/Transparent.png")) {
        std::cout << "не удалось установить передний спрайт в конструкторе GameTile" << std::endl;
        return;
    }
}

/* Устанавливает фоновую текстуру для каждого тайла */
bool GameTile::setUpBackSprite(std::string backTextureFilename)
{
    if (!backTexture.loadFromFile(backTextureFilename))
    {
        std::cout << "ошибка загрузки текстуры из файла: " << backTextureFilename << "." << std::endl;
        return false;
    }

    backSprite.setTexture(backTexture);
    backSprite.setPosition(pos);
    return true;
}

/* Устанавливает фоновую текстуру для каждого тайла (с указанием позиции в текстуре) */
bool GameTile::setUpBackSprite(std::string backTextureFilename, int pos_x, int pos_y)
{
    if (!backTexture.loadFromFile(backTextureFilename, sf::IntRect(pos_x, pos_y, GAMETILE_DIM / 2, GAMETILE_DIM / 2)))
    {
        std::cout << "ошибка загрузки текстуры из файла: " << backTextureFilename << "." << std::endl;
        return false;
    }

    backSprite.setTexture(backTexture);
    backSprite.setPosition(pos);
    return true;
}

/* Устанавливает переднюю текстуру для каждого тайла */
bool GameTile::setUpFrontSprite(std::string frontTextureFilename)
{
    if (!frontTexture.loadFromFile(frontTextureFilename, sf::IntRect(0, 0, GAMETILE_DIM / 2, GAMETILE_DIM - 1)))
    {
        std::cout << "ошибка загрузки текстуры из файла: " << frontTextureFilename << "." << std::endl;
        return false;
    }
    frontSprite.setTexture(frontTexture);
    frontSprite.setScale(2, 2); // Устанавливает масштаб для изображений
    frontSprite.setOrigin(0, frontTexture.getSize().y);
    sf::Vector2f bottomLeftAdjustedPos(pos.x, pos.y + GAMETILE_DIM);
    frontSprite.setPosition(bottomLeftAdjustedPos);
    return true;
}

/* Устанавливает переднюю текстуру для каждого тайла (с указанием позиции в текстуре) */
bool GameTile::setUpFrontSprite(std::string frontTextureFilename, int pos_x, int pos_y)
{
    if (!frontTexture.loadFromFile(frontTextureFilename, sf::IntRect(pos_x, pos_y, GAMETILE_DIM / 2, GAMETILE_DIM / 2)))
    {
        std::cout << "ошибка загрузки текстуры из файла: " << frontTextureFilename << "." << std::endl;
        return false;
    }
    frontSprite.setTexture(frontTexture);
    frontSprite.setScale(2, 2); // Устанавливает масштаб для изображений
    frontSprite.setOrigin(0, frontTexture.getSize().y);
    sf::Vector2f bottomLeftAdjustedPos(pos.x, pos.y + GAMETILE_DIM);
    frontSprite.setPosition(bottomLeftAdjustedPos);
    return true;
}

void GameTile::set_pos(float pos_x, float pos_y) {
    pos = sf::Vector2f(pos_x, pos_y);
}

sf::Vector2f GameTile::get_pos() {
    return(pos);
}

/* Рисует рамку выделения на тайле */
void GameTile::drawSelectionBox(sf::RenderWindow* window)
{
    if (!selectionBoxTexture.loadFromFile("sprites/selectionBox.png"))
    {
        std::cout << "ошибка загрузки текстуры рамки выделения из файла." << std::endl;
    }
    selectionBoxSprite.setTexture(selectionBoxTexture);
    selectionBoxSprite.setPosition(pos);
    window->draw(selectionBoxSprite);
}