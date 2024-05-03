#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <windows.h>
#include <vector>
#include <cmath>

using namespace std;

COLORREF getPixelColor(int x, int y);

void openWebsite(const char *url);

void sendKeystrokes(char key);

void printState(std::vector<std::vector<int>> state);

void startGame();

char findBestMove(std::vector<std::vector<int>> state);

bool isDead(std::vector<std::vector<int>> state);

vector<vector<int>> createStateVector();

vector<POINT> createGameSpace();

int tileValue(POINT p);

void getCoordinates();


#endif //UTILS_H
