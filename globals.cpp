#include "globals.h"

char item_names[MAX_ITEMS][MAX_NAME_LEN] = {
    "Пусто", "Дерево", "Камень", "Семена", "Железо",
    "Хлеб",  "Золото", "Алмазы", "Уголь", "Факел"
};

int  inventory[INVENTORY_SIZE] = {};
char farmer_name[FARMER_NAME_LEN + 1] = "Безымянный";