#include "inventory.h"
#include "globals.h"
#include "constants.h"
#include "console.h"
#include "items.h"
#include <iostream>
#include <cstring>

void initInventory() {
    for (int& slot : inventory) slot = ID_nothing;
    if (INVENTORY_SIZE > 4) {
        inventory[1] = ID_wood;
        inventory[2] = ID_stone;
        inventory[3] = ID_seed;
        inventory[4] = ID_iron;
    }
}

void showInventory() {
    std::cout << "\n--- Инвентарь " << farmer_name << " ---\n";
    for (int i = 0; i < INVENTORY_SIZE; ++i)
        std::cout << "Слот " << i << ": [" << inventory[i] << "] - "
        << item_names[inventory[i]] << "\n";
}

void placeItem() {
    const int slot = readInt(0, INVENTORY_SIZE - 1, "Введите номер слота (0-9): ");
    const int id = readInt(0, MAX_ITEMS - 1, "Введите ID предмета (0-9): ");
    inventory[slot] = id;
    std::cout << "В слот " << slot << " помещен: " << item_names[id] << "\n";
}

void dropItem() {
    const int slot = readInt(0, INVENTORY_SIZE - 1,
        "Введите номер слота (0-9), чтобы очистить: ");
    inventory[slot] = ID_nothing;
    std::cout << "Слот " << slot << " очищен.\n";
}

void auditResources() {
    const int target = readInt(0, MAX_ITEMS - 1, "Введите ID предмета для поиска: ");
    int total = 0;
    std::cout << item_names[target] << " (ID " << target << ") в слотах: ";
    for (int i = 0; i < INVENTORY_SIZE; ++i)
        if (inventory[i] == target) { std::cout << i << " "; ++total; }
    if (!total) std::cout << "отсутствует";
    std::cout << "\nКоличество: " << total << "\n";
}

void searchItemByName() {
    char query[MAX_NAME_LEN];
    readLine(query, MAX_NAME_LEN, "Введите название предмета для поиска: ");
    const int id = findItemIdByName(query);
    if (id < 0) {
        std::cout << "Предмет \"" << query << "\" не найден в каталоге.\n";
        return;
    }
    bool any = false;
    std::cout << "\"" << query << "\" (ID " << id << ") в слотах: ";
    for (int i = 0; i < INVENTORY_SIZE; ++i)
        if (inventory[i] == id) { std::cout << i << " "; any = true; }
    if (!any) std::cout << "отсутствует";
    std::cout << "\n";
}