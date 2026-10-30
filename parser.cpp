#include "parser.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

void parseConfig() {
    std::ifstream in("input.txt");
    if (!in.is_open()) {
        std::cout << "Ошибка: input.txt не найден.\n";
        return;
    }
    std::ofstream out("output.txt");
    if (!out.is_open()) {
        std::cout << "Ошибка: output.txt не открыт.\n";
        return;
    }

    std::vector<std::pair<std::string, std::string>> settings;
    int ok = 0, dropped = 0;
    std::string raw;

    std::cout << "\n--- Чистая таблица настроек ---\n";
    while (std::getline(in, raw)) {
        auto first = std::find_if(raw.begin(), raw.end(),
            [](unsigned char c) { return !std::isspace(c); });
        if (first == raw.end()) { ++dropped; continue; }
        auto last = std::find_if(raw.rbegin(), raw.rend(),
            [](unsigned char c) { return !std::isspace(c); }).base();
        std::string line(first, last);

        if (line.empty() || line[0] == '#') { ++dropped; continue; }
        const size_t eq = line.find('=');
        if (eq == std::string::npos) { ++dropped; continue; }

        std::string key = line.substr(0, eq);
        std::string val = line.substr(eq + 1);
        while (!key.empty() && std::isspace((unsigned char)key.back()))  key.pop_back();
        while (!val.empty() && std::isspace((unsigned char)val.front())) val.erase(val.begin());
        if (key.empty() || val.empty()) { ++dropped; continue; }

        settings.emplace_back(key, val);
        std::cout << "Параметр: [" << key << "] | Значение: [" << val << "]\n";
        ++ok;
    }

    std::cout << "\nСтатистика: " << ok << " считано, " << dropped << " отброшено.\n";
    out << "Результат парсинга input.txt\n";
    for (const auto& [k, v] : settings) out << k << '=' << v << '\n';
    std::cout << "Сохранено в output.txt\n";
}