#ifndef BOT_H
#define BOT_H

#include <iostream>
#include <windows.h>
#include <vector>
#include <cmath>

using namespace std;

char findBestMove(vector<vector<int>> state);

double valueOfState(vector<vector<int>> state);

void nextState(vector<vector<int>>& state, char c);

#endif //BOT_H
