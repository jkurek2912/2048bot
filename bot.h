#ifndef BOT_H
#define BOT_H

#include <iostream>
#include <windows.h>
#include <vector>
#include <cmath>

using namespace std;

char findBestMove(vector<vector<int>> state);

double valueOfState(vector<vector<int>> state, int p);

bool nextState(vector<vector<int>> &state, char c);

bool moveUp(vector<vector<int>> &state);

bool moveDown(vector<vector<int>> &state);

bool moveLeft(vector<vector<int>> &state);

bool moveRight(vector<vector<int>> &state);

vector<pair<int, vector<vector<int>>>> permutations(vector<vector<int>>& state);

double maxValueLocationBoost(int x, int y);

#endif //BOT_H
