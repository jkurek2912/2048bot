#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <windows.h>
#include <vector>
#include <cmath>

COLORREF getPixelColor(int x, int y);
void openWebsite(const char *url);
void sendKeystrokes(const char key);
void printState(std::vector<std::vector<int>> state);
void startGame();

#endif //UTILS_H
