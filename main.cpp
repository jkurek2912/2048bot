#include <iostream>
#include <windows.h>
#include <vector>
#include <cmath>
#include "utils.h"

using namespace std;

// Vector to store the RGB values of states 2 - 4096
vector<vector<int>> rgbValues = {{238, 228, 218},
                                 {237, 224, 200},
                                 {242, 177, 121},
                                 {245, 149, 99},
                                 {246, 124, 95},
                                 {246, 94,  59},
                                 {237, 207, 114},
                                 {237, 204, 97},
                                 {237, 200, 80},
                                 {237, 197, 63},
                                 {237, 194, 64},
                                 {181, 134, 180},
                                 {168, 97,  171}};


// Gets the tile value given a coordinate
int tileValue(POINT p) {
    COLORREF color = getPixelColor(p.x, p.y);
    int r = GetRValue(color);
    int g = GetGValue(color);
    int b = GetBValue(color);
    int val = 0;
    for (int i = 0; i < rgbValues.size(); i++) {
        if (abs(r - rgbValues[i][0]) <= 5 && abs(g - rgbValues[i][1]) <= 5 && abs(b - rgbValues[i][2]) <= 5) {
            val = pow(2, i + 1);
            break;
        }
    }
    return val;
}

// Initializes array of coordinates
vector<POINT> createGameSpace() {
    vector<POINT> pos(16);
    int points = 0;
    while (points < 16) {
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            GetCursorPos(&pos[points]);
            points++;
            Sleep(150);
        }
    }
    return pos;
}



// Creates 2d vector to represent the grid
vector<vector<int>> createStateVector(vector<POINT> points) {
    vector<vector<int>> res;
    vector<int> temp;
    for (int i = 0; i < points.size(); i++) {
        temp.push_back(tileValue(points[i]));
        if ((i + 1) % 4 == 0) {
            res.push_back(temp);
            temp.clear();
        }
    }
    return res;
}

// Checks if there are legal moves remaining
bool isDead(vector<vector<int>> state) {
    vector<vector<int>> neighbors = {{0,  1},
                                     {1,  0},
                                     {-1, 0},
                                     {0,  -1}};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int l = 0; l < 4; l++) {
                if (i + neighbors[l][0] < 4 && i + neighbors[l][0] >= 0 && j + neighbors[l][1] < 4 &&
                    j + neighbors[l][1] >= 0) {
                    int x = i + neighbors[l][0];
                    int y = j + neighbors[l][1];
                    if (state[i][j] == state[x][y] || state[i][j] == 0) return false;
                }
            }
        }
    }
    return true;
}

int main() {
    startGame();
    vector<POINT> points = createGameSpace();
    vector<vector<int>> state = createStateVector(points);
    while (!isDead(state)) {
        //char c = findBestMove(state);
        sendKeystrokes('w');
        sendKeystrokes('a');
        sendKeystrokes('s');
        sendKeystrokes('d');
        state = createStateVector(points);
    }
}
