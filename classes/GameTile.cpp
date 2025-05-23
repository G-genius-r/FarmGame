#include "../headers/GameTile.h"

#define GAMETILE_DIM 32

GameTile::GameTile(std::string backTextureFilename, float pos_x, float pos_y)
{
    pos = sf::Vector2f(pos_x, pos_y);
    if (!setUpBackSprite(backTextureFilename)) {
        std::cout << "�� ������� ���������� ������� ������ � ������������ GameTile" << std::endl;
        return;
    }
    if (!setUpFrontSprite("sprites/Transparent.png")) {
        std::cout << "�� ������� ���������� �������� ������ � ������������ GameTile" << std::endl;
        return;
    }
}

/* ������������� ������� �������� ��� ������� ����� */
bool GameTile::setUpBackSprite(std::string backTextureFilename)
{
    if (!backTexture.loadFromFile(backTextureFilename))
    {
        std::cout << "������ �������� �������� �� �����: " << backTextureFilename << "." << std::endl;
        return false;
    }

    backSprite.setTexture(backTexture);
    backSprite.setPosition(pos);
    return true;
}

/* ������������� ������� �������� ��� ������� ����� (� ��������� ������� � ��������) */
bool GameTile::setUpBackSprite(std::string backTextureFilename, int pos_x, int pos_y)
{
    if (!backTexture.loadFromFile(backTextureFilename, sf::IntRect(pos_x, pos_y, GAMETILE_DIM / 2, GAMETILE_DIM / 2)))
    {
        std::cout << "������ �������� �������� �� �����: " << backTextureFilename << "." << std::endl;
        return false;
    }

    backSprite.setTexture(backTexture);
    backSprite.setPosition(pos);
    return true;
}

/* ������������� �������� �������� ��� ������� ����� */
// ��������� ������ ������ cellWidth, cellHeight ��� ������!
bool GameTile::setUpFrontSprite(std::string frontTextureFilename)
{
    // ������� ����������: ������ �������� � ��������� ��������
    if (!frontTexture.loadFromFile(frontTextureFilename)) {
        std::cout << "������ �������� �������� �� �����: " << frontTextureFilename << "." << std::endl;
        return false;
    }
    frontSprite.setTexture(frontTexture);
    return true;
}

/* ������������� �������� �������� ��� ������� ����� (� ��������� ������� � ��������) */
bool GameTile::setUpFrontSprite(std::string frontTextureFilename, float cellWidth, float cellHeight)
{
    if (!frontTexture.loadFromFile(frontTextureFilename, sf::IntRect(0, 0, GAMETILE_DIM / 2, GAMETILE_DIM - 1)))
    {
        std::cout << "������ �������� �������� �� �����: " << frontTextureFilename << "." << std::endl;
        return false;
    }
    frontSprite.setTexture(frontTexture);

    float scaleX = cellWidth / frontTexture.getSize().x;
    float scaleY = cellHeight / frontTexture.getSize().y;
    frontSprite.setScale(scaleX, scaleY);

    frontSprite.setOrigin(0, frontTexture.getSize().y * scaleY);
    sf::Vector2f bottomLeftAdjustedPos(pos.x, pos.y + cellHeight);
    frontSprite.setPosition(bottomLeftAdjustedPos);

    return true;
}

void GameTile::setScale(float width, float height) {
    if (frontSprite.getTexture()) {
        float scaleX = width / frontSprite.getTextureRect().width;
        float scaleY = height / frontSprite.getTextureRect().height;
        frontSprite.setScale(scaleX, scaleY);
    }
    if (backSprite.getTexture()) {
        float scaleX = width / backSprite.getTextureRect().width;
        float scaleY = height / backSprite.getTextureRect().height;
        backSprite.setScale(scaleX, scaleY);
    }
    if (selectionBoxSprite.getTexture()) {
        float scaleX = width / selectionBoxSprite.getTextureRect().width;
        float scaleY = height / selectionBoxSprite.getTextureRect().height;
        selectionBoxSprite.setScale(scaleX, scaleY);
    }
}

void GameTile::set_pos(float pos_x, float pos_y) {
    pos = sf::Vector2f(pos_x, pos_y);
    frontSprite.setPosition(pos);
    backSprite.setPosition(pos);
    selectionBoxSprite.setPosition(pos);
}

sf::Vector2f GameTile::get_pos() {
    return pos;
}

void GameTile::drawSelectionBox(sf::RenderWindow* window)
{
    if (!selectionBoxTexture.loadFromFile("sprites/selectionBox.png"))
    {
        std::cout << "������ �������� �������� ����� ��������� �� �����." << std::endl;
    }
    selectionBoxSprite.setTexture(selectionBoxTexture);
    selectionBoxSprite.setPosition(pos);
    window->draw(selectionBoxSprite);
}