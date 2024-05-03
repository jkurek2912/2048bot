#ifndef BOT_H
#define BOT_H

#include <iostream>
#include <windows.h>
#include <vector>
#include <cmath>

using namespace std;

char findBestMove(vector<vector<int>> state);

int valueOfState(vector<vector<int>> state);

vector<vector<int>> generateStates(vector<vector<int>> state);

#endif //BOT_H
