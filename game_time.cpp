#include "game_time.h"
#include "console.h"
#include "constants.h"
#include <iostream>

void printTime(int day, int hour) {
    std::cout << "Текущее время: День " << day << ", "
        << formatClock(hour) << "\n";
}

void advanceTime(int& day, int& hour, int add) {
    hour += add;
    if (hour >= HOURS_IN_DAY) {
        day += hour / HOURS_IN_DAY;
        hour %= HOURS_IN_DAY;
    }
}