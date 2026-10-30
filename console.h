#pragma once
#include <string>

int         readInt(int lo, int hi, const std::string& prompt);
void        readLine(char* out, int size, const std::string& prompt);
std::string formatClock(int hour);