#include "items.h"
#include "globals.h"
#include "constants.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <cctype>

// atoi("Дерево") молча вернёт 0 — получили бы ложный ID. Свой парсер.
static bool parseLeadingInt(const std::string& line, int& out_id, size_t& used) {
    size_t i = 0;
    while (i < line.size() && std::isspace((unsigned char)line[i])) ++i;
    if (i >= line.size() || !std::isdigit((unsigned char)line[i])) return false;

    long value = 0;
    const size_t start = i;
    while (i < line.size() && std::isdigit((unsigned char)line[i])) {
        value = value * 10 + (line[i++] - '0');
        if (value > 100000) return false;
    }
    out_id = (int)value;
    used = i - start;
    return true;
}

void loadItemNames() {
    std::ifstream f("items.txt");
    if (!f.is_open()) {
        std::cout << "Предупреждение: items.txt не найден. Стандартные названия.\n";
        return;
    }
    std::string line;
    int next_auto_id = 0;
    while (std::getline(f, line)) {
        if (line.empty()) continue;

        int item_id = next_auto_id;
        std::string item_name = line;

        int parsed;
        size_t used;
        if (parseLeadingInt(line, parsed, used)) {
            item_id = parsed;
            const size_t sp = line.find(' ', used);
            item_name = (sp == std::string::npos) ? "" : line.substr(sp + 1);
        }
        if (item_id < 0 || item_id >= MAX_ITEMS || item_name.empty()) continue;
        if (item_name.size() >= (size_t)MAX_NAME_LEN) item_name.resize(MAX_NAME_LEN - 1);

        std::strncpy(item_names[item_id], item_name.c_str(), MAX_NAME_LEN - 1);
        item_names[item_id][MAX_NAME_LEN - 1] = '\0';
        ++next_auto_id;
    }
}

int findItemIdByName(const char* name) {
    for (int i = 0; i < MAX_ITEMS; ++i)
        if (std::strcmp(item_names[i], name) == 0) return i;
    return -1;
}