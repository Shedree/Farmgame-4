#include <cstring>
#include <iostream>
#include <string>
#include <windows.h>
#include "constants.h"
#include "globals.h"
#include "console.h"
#include "items.h"
#include "inventory.h"
#include "game_time.h"
#include "diary.h"
#include "parser.h"
#include "adventure.h"   // ← новый модуль

using std::cin;
using std::cout;

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    readLine(farmer_name, FARMER_NAME_LEN + 1,
        "Введите имя вашего фермера (до 32 символов): ");
    if (farmer_name[0] == '\0') {
        std::strncpy(farmer_name, "Безымянный фермер", FARMER_NAME_LEN);
        farmer_name[FARMER_NAME_LEN] = '\0';
    }
    loadItemNames();
    initInventory();

    int current_day = 1;
    int current_hour = 8;
    int choice;

    do {
        cout << "\n=== Ферма " << farmer_name << " | День " << current_day
            << " | " << formatClock(current_hour) << " ===\n";
        cout << "1. Показать время\n";
        cout << "2. Работать (добавить часы)\n";
        cout << "3. Показать инвентарь\n";
        cout << "4. Положить предмет в слот\n";
        cout << "5. Выбросить предмет\n";
        cout << "6. Ревизия ресурсов (ID)\n";
        cout << "7. Поиск предмета по названию\n";
        cout << "8. Записать состояние в дневник\n";
        cout << "9. Расшифровать input.txt (парсер .ini)\n";
        cout << "10. Отправиться в приключение\n";
        cout << "0. Выход\n";

        choice = readInt(0, MENU_ITEMS_COUNT, "Выберите действие: ");

        switch (choice) {
        case 0:
            cout << "Выход. До свидания, " << farmer_name << "!\n";
            break;
        case 1: printTime(current_day, current_hour); break;
        case 2: {
            const int hours = readInt(0, MAX_WORK_HOURS,
                "Сколько часов потратить на работу (0-"
                + std::to_string(MAX_WORK_HOURS) + ")? ");
            advanceTime(current_day, current_hour, hours);
            break;
        }
        case 3: showInventory();    break;
        case 4: placeItem();        break;
        case 5: dropItem();         break;
        case 6: auditResources();   break;
        case 7: searchItemByName(); break;
        case 8: writeDiary(current_day, current_hour); break;
        case 9: parseConfig();      break;
        case 10: runAdventure();    break;   // ← п.10
        default:
            cout << "Неизвестный пункт меню.\n";
            break;
        }
    } while (choice != 0);

    return 0;
}