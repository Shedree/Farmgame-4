#include "diary.h"
#include "globals.h"
#include "constants.h"
#include "console.h"
#include <fstream>
#include <iostream>

void writeDiary(int day, int hour) {
    std::ofstream f("diary.txt", std::ios::app);
    if (!f.is_open()) {
        std::cout << "Ошибка: diary.txt не открыт.\n";
        return;
    }
    f << "=== Запись в дневнике ===\n"
        << "Фермер: " << farmer_name << "\n"
        << "Время: День " << day << ", " << formatClock(hour) << "\n"
        << "Инвентарь:\n";
    for (int i = 0; i < INVENTORY_SIZE; ++i)
        f << "  Слот " << i << ": [" << inventory[i] << "] - "
        << item_names[inventory[i]] << "\n";
    f << "=========================\n\n";
    std::cout << "Состояние успешно записано в diary.txt\n";
}