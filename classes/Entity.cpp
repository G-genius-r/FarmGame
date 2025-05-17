#include "../headers/Entity.h"

// Конструктор класса Entity
Entity::Entity() {
    // Конструктор по умолчанию, не требует специальной инициализации
}

// Получение текущей стадии роста сущности
int Entity::get_growthStage() {
    return growthStage; // Возвращает стадию роста
}

// Получение уровня полива сущности
int Entity::get_isWatered() {
    return wateringLevel; // Возвращает уровень полива
}

// Установка стадии роста сущности
void Entity::set_growthStage(int _growthStage) {
    growthStage = _growthStage; // Устанавливает стадию роста
}

// Установка уровня полива сущности
void Entity::set_isWatered(int _wateringLevel) {
    wateringLevel = _wateringLevel; // Устанавливает уровень полива
}

// Получение количества яиц (не для всех сущностей)
int Entity::getEggs() {
    std::cout << "Нельзя получить яйца - сущность не является курицей" << std::endl;
    return 0; // Возвращает 0, так как это не курица
}

// Проверка наличия шерсти (не для всех сущностей)
bool Entity::getWool() {
    std::cout << "Нельзя получить шерсть - сущность не является овцой" << std::endl;
    return 0; // Возвращает false, так как это не овца
}

// Установка количества яиц (не для всех сущностей)
void Entity::setEggs(int _Eggs) {
    _Eggs = isPlant; // Некорректное присваивание (вероятно, должно быть isPlant = _Eggs)
    isPlant = _Eggs;
    std::cout << "Нельзя установить яйца - сущность не является курицей" << std::endl;
}

// Установка наличия шерсти (не для всех сущностей)
void Entity::setWool(bool _Wool) {
    _Wool = isPlant; // Некорректное присваивание (вероятно, должно быть isPlant = _Wool)
    isPlant = _Wool;
    std::cout << "Нельзя установить шерсть - сущность не является овцой" << std::endl;
}

// Установка флага "является растением"
void Entity::set_isPlant(bool _isPlant) {
    isPlant = _isPlant; // Устанавливает флаг растения
}

// Установка флага "является животным"
void Entity::set_isAnimal(bool _isAnimal) {
    isAnimal = _isAnimal; // Устанавливает флаг животного
}

// Проверка, является ли сущность растением
bool Entity::get_isPlant() {
    return isPlant; // Возвращает флаг растения
}

// Проверка, является ли сущность животным
bool Entity::get_isAnimal() {
    return isAnimal; // Возвращает флаг животного
}

// Симуляция поедания зерна (не для всех сущностей)
bool Entity::eatGrain(Inventory*) {
    return false; // Возвращает false, так как поедание зерна не применимо
}

// Получение корректного имени файла текстуры для сущности
std::string Entity::getCorrectFilename()
{
    if (this->get_type() == 4) { // Если это овца (специальный случай)
        if (this->getWool() == true) // Если есть шерсть
            return(textureFilenames[1]); // Возвращает текстуру с шерстью
        else
            return(textureFilenames[0]); // Возвращает обычную текстуру
    }
    return(textureFilenames[growthStage]); // Возвращает текстуру в зависимости от стадии роста
}

// Симуляция удобрения (не для всех сущностей)
void Entity::fertilise(Inventory* Inventory) {
    Inventory->eggsAdd(0); // Добавляет яйца (некорректное название функции, должно быть связано с шерстью или растениями)
}