#pragma once

// Структура карты: двумерный динамический массив + размеры + позиция героя
struct GameMap {
    char** cells;   // cells[y][x]
    int    width;   // столбцы
    int    height;  // строки
    int    heroX;
    int    heroY;
};

// Выделение и освобождение
bool   allocateMap(GameMap& map, int w, int h);
void   freeMap(GameMap& map);          // безопасно вызывать повторно

// Генерация
bool   generateMap(GameMap& map);      // случайный размер, стены, препятствия, герой
bool   generateMapWithSize(GameMap& map, int w, int h); // для тестов/повторов

// Работа с картой
void   printMap(const GameMap& map);
bool   moveHero(GameMap& map, int dx, int dy); // true, если герой сдвинулся

// Утилиты
bool   isInside(const GameMap& map, int x, int y);
bool   isWalkable(const GameMap& map, int x, int y);
void   findFreeCell(const GameMap& map, int& outX, int& outY);