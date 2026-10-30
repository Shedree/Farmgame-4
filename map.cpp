#include "map.h"
#include "constants.h"
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <iostream>

// ---- Выделение памяти ----
bool allocateMap(GameMap& map, int w, int h) {
    map.width  = w;
    map.height = h;
    map.heroX  = 0;
    map.heroY  = 0;

    // 1) массив указателей (строк)
    map.cells = (char**)malloc(h * sizeof(char*));
    if (!map.cells) return false;

    // 2) в каждой строке — массив символов
    for (int i = 0; i < h; ++i) {
        map.cells[i] = (char*)malloc(w * sizeof(char));
        if (!map.cells[i]) {
            // аккуратно освобождаем уже выделенное — иначе утечка
            for (int k = 0; k < i; ++k) free(map.cells[k]);
            free(map.cells);
            map.cells = nullptr;
            map.width = map.height = 0;
            return false;
        }
    }
    return true;
}

// ---- Освобождение в обратном порядке ----
void freeMap(GameMap& map) {
    if (!map.cells) return;
    for (int i = 0; i < map.height; ++i) {
        free(map.cells[i]);
    }
    free(map.cells);
    map.cells  = nullptr;
    map.width  = 0;
    map.height = 0;
    map.heroX  = 0;
    map.heroY  = 0;
}

// ---- Проверки границ / проходимости ----
bool isInside(const GameMap& map, int x, int y) {
    return x >= 0 && x < map.width && y >= 0 && y < map.height;
}

bool isWalkable(const GameMap& map, int x, int y) {
    if (!isInside(map, x, y)) return false;
    char c = map.cells[y][x];
    return c != TILE_WALL && c != TILE_TREE && c != TILE_ROCK;
}

// ---- Поиск случайной свободной клетки ----
void findFreeCell(const GameMap& map, int& outX, int& outY) {
    for (int attempt = 0; attempt < MAX_GENERATION_TRIES; ++attempt) {
        int x = rand() % map.width;
        int y = rand() % map.height;
        if (map.cells[y][x] == TILE_FLOOR) {
            outX = x;
            outY = y;
            return;
        }
    }
    // fallback — просто первая свободная
    for (int y = 1; y < map.height - 1; ++y) {
        for (int x = 1; x < map.width - 1; ++x) {
            if (map.cells[y][x] == TILE_FLOOR) {
                outX = x;
                outY = y;
                return;
            }
        }
    }
    outX = 1;
    outY = 1;
}

// ---- Генерация с явными размерами ----
bool generateMapWithSize(GameMap& map, int w, int h) {
    // на всякий случай очищаем старую карту (безопасно, если её нет)
    freeMap(map);

    if (!allocateMap(map, w, h)) {
        std::cout << "Ошибка: не удалось выделить память под карту.\n";
        return false;
    }

    // Вероятность препятствий (15..30%)
    int chance = OBSTACLE_PERCENT_MIN +
                 rand() % (OBSTACLE_PERCENT_MAX - OBSTACLE_PERCENT_MIN + 1);

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            // Внешние границы — стены
            if (x == 0 || y == 0 || x == w - 1 || y == h - 1) {
                map.cells[y][x] = TILE_WALL;
            } else {
                int roll = rand() % 100;
                if (roll < chance) {
                    map.cells[y][x] =
                        (rand() % 2 == 0) ? TILE_TREE : TILE_ROCK;
                } else {
                    map.cells[y][x] = TILE_FLOOR;
                }
            }
        }
    }

    // Ставим героя на случайную свободную клетку
    int hx, hy;
    findFreeCell(map, hx, hy);
    map.cells[hy][hx] = TILE_HERO;
    map.heroX = hx;
    map.heroY = hy;
    return true;
}

// ---- Генерация со случайным размером 5..30 ----
bool generateMap(GameMap& map) {
    int w = MAP_MIN_SIZE + rand() % (MAP_MAX_SIZE - MAP_MIN_SIZE + 1);
    int h = MAP_MIN_SIZE + rand() % (MAP_MAX_SIZE - MAP_MIN_SIZE + 1);
    return generateMapWithSize(map, w, h);
}

// ---- Печать карты ----
void printMap(const GameMap& map) {
    if (!map.cells) {
        std::cout << "Карта пуста.\n";
        return;
    }
    std::cout << "\n   ";
    for (int x = 0; x < map.width; ++x) {
        if (x < 10) std::cout << x << " ";
        else        std::cout << (x % 10) << " ";
    }
    std::cout << "\n";

    for (int y = 0; y < map.height; ++y) {
        if (y < 10) std::cout << y << "  ";
        else        std::cout << y << " ";
        for (int x = 0; x < map.width; ++x) {
            std::cout << map.cells[y][x] << " ";
        }
        std::cout << "\n";
    }
}

// ---- Перемещение героя ----
bool moveHero(GameMap& map, int dx, int dy) {
    int nx = map.heroX + dx;
    int ny = map.heroY + dy;
    if (!isWalkable(map, nx, ny)) {
        std::cout << "Туда нельзя пройти.\n";
        return false;
    }
    // стираем старого героя
    map.cells[map.heroY][map.heroX] = TILE_FLOOR;
    // ставим нового
    map.heroX = nx;
    map.heroY = ny;
    map.cells[ny][nx] = TILE_HERO;
    return true;
}