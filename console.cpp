#include "console.h"
#include "constants.h"
#include <iostream>
#include <string>
#include <cstring>

int readInt(int lo, int hi, const std::string& prompt) {
    int v;
    while (true) {
        std::cout << prompt;
        if (std::cin >> v) {
            if (v >= lo && v <= hi) {
                std::cin.ignore(INPUT_FLUSH_LIMIT, '\n');
                return v;
            }
            std::cout << "Ошибка! Число должно быть от " << lo
                << " до " << hi << ".\n";
        }
        else {
            std::cout << "Ошибка! Введите целое число.\n";
            std::cin.clear();
            std::cin.ignore(INPUT_FLUSH_LIMIT, '\n');
        }
    }
}

void readLine(char* out, int size, const std::string& prompt) {
    std::cout << prompt;
    std::string in;
    std::getline(std::cin, in);
    std::strncpy(out, in.c_str(), size - 1);
    out[size - 1] = '\0';
}

std::string formatClock(int hour) {
    return (hour < 10 ? "0" : "") + std::to_string(hour) + ":00";
}