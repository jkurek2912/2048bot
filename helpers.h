#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <windows.h>
#include <vector>
#include <cmath>
#include <random>

using namespace std;

void printState(vector<vector<int>> state);

void getCoordinate();

char getRandomDirection();

vector<vector<int>> makeState();

#endif //HELPERS_H
