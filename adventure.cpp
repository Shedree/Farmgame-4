#include "adventure.h"
#include "map.h"
#include "console.h"
#include "constants.h"   // ← для WIND_PUSH_DIST
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <ctime>

static char readDirection() {
    while (true) {
        std::cout << "Действие (W - вверх, A - влево, S - вниз, D - вправо, Q - домой): ";
        std::string line;
        if (!std::getline(std::cin, line)) return 'Q';
        if (line.empty()) continue;
        char c = (char)std::toupper((unsigned char)line[0]);
        if (c == 'W' || c == 'A' || c == 'S' || c == 'D' || c == 'Q') return c;
        std::cout << "Неверный ввод. Допустимо: W, A, S, D, Q.\n";
    }
}

void runAdventure() {
    std::srand((unsigned)std::time(nullptr));

    GameMap map{};
    if (!generateMap(map)) {
        std::cout << "Не удалось создать карту.\n";
        return;
    }

    std::cout << "\n=== ПРИКЛЮЧЕНИЕ НАЧАЛОСЬ ===\n";
    std::cout << "Размер карты: " << map.width << " x " << map.height << "\n";
    std::cout << "Стрелки ^ v < > — сквозняк: сдувает на "
              << WIND_PUSH_DIST << " клетки.\n";

    bool active = true;
    while (active) {
        printMap(map);
        char cmd = readDirection();
        switch (cmd) {
            case 'W': moveHero(map,  0, -1); break;
            case 'S': moveHero(map,  0,  1); break;
            case 'A': moveHero(map, -1,  0); break;
            case 'D': moveHero(map,  1,  0); break;
            case 'Q':
                std::cout << "Возвращаемся на ферму...\n";
                active = false;
                break;
            default: break;
        }
    }

    freeMap(map);
    std::cout << "=== ПРИКЛЮЧЕНИЕ ЗАВЕРШЕНО ===\n";
}