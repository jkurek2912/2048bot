#include "bot.h"
#include "helpers.h"
#include "utils.h"


char findBestMove(vector<vector<int>> state) {
    vector<vector<int>> w = state;
    vector<vector<int>> a = state;
    vector<vector<int>> s = state;
    vector<vector<int>> d = state;
    char bestMove = 'w';
    double max = 0;

    if (nextState(w, 'w')) {
        vector<pair<int, vector<vector<int>>>> wMoves = permutations(w);
        double wScore = 0;
        for (auto & wMove : wMoves) {
            wScore += valueOfState(wMove.second, wMove.first);
        }
        wScore /= (double) wMoves.size();
        if (wScore >= max) {
            max = wScore;
            bestMove = 'w';
        }
    }

    if (nextState(a, 'a')) {
        vector<pair<int, vector<vector<int>>>> aMoves = permutations(a);
        double aScore = 0;
        for (auto & aMove : aMoves) {
            aScore += valueOfState(aMove.second, aMove.first);
        }
        aScore /= (double) aMoves.size();
        if (aScore >= max) {
            max = aScore;
            bestMove = 'a';
        }
    }

    if (nextState(s, 's')) {
        vector<pair<int, vector<vector<int>>>> sMoves = permutations(s);
        double sScore = 0;
        for (auto & sMove : sMoves) {
            sScore += valueOfState(sMove.second, sMove.first);
        }
        sScore /= (double) sMoves.size();
        if (sScore >= max) {
            max = sScore;
            bestMove = 's';
        }
    }

    if (nextState(d, 'd')) {
        vector<pair<int, vector<vector<int>>>> dMoves = permutations(d);
        double dScore = 0;
        for (auto & dMove : dMoves) {
            dScore += valueOfState(dMove.second, dMove.first);
        }
        dScore /= (double) dMoves.size();
        if (dScore >= max) {
            max = dScore;
            bestMove = 'd';
        }
    }
    return bestMove;
}

bool nextState(vector<vector<int>> &state, char c) {
    bool moved;
    switch (c) {
        case 'w':
            moved = moveUp(state);
            break;
        case 'a':
            moved = moveLeft(state);
            break;
        case 's':
            moved = moveDown(state);
            break;
        default:
            moved = moveRight(state);
            break;
    }
    return moved;
}

bool moveUp(vector<vector<int>> &state) {
    bool moved = false;
    for (int i = 1; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int x = i;
            while (x > 0 && (state[x - 1][j] == 0 || state[x - 1][j] == state[x][j]) && state[x][j] != 0) {
                if (state[x - 1][j] == state[x][j]) {
                    state[x - 1][j] *= 2;
                } else {
                    state[x - 1][j] = state[x][j];
                }
                state[x][j] = 0;
                x--;
                moved = true;
            }
        }
    }
    return moved;
}

bool moveDown(vector<vector<int>> &state) {
    bool moved = false;
    for (int i = 3; i >= 0; i--) {
        for (int j = 0; j < 4; j++) {
            int x = i;
            while (x < 3 && (state[x + 1][j] == 0 || state[x + 1][j] == state[x][j]) && state[x][j] != 0) {
                if (state[x + 1][j] == state[x][j]) {
                    state[x + 1][j] *= 2;
                } else {
                    state[x + 1][j] = state[x][j];
                }
                state[x][j] = 0;
                x++;
                moved = true;
            }
        }
    }
    return moved;
}

bool moveLeft(vector<vector<int>> &state) {
    bool moved = false;
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j < 4; j++) {
            int x = j;
            while (x > 0 && (state[i][x - 1] == 0 || state[i][x - 1] == state[i][x]) && state[i][x] != 0) {
                if (state[i][x - 1] == state[i][x]) {
                    state[i][x - 1] *= 2;
                } else {
                    state[i][x - 1] = state[i][x];
                }
                state[i][x] = 0;
                x--;
                moved = true;
            }
        }
    }
    return moved;
}

bool moveRight(vector<vector<int>> &state) {
    bool moved = false;
    for (int i = 0; i < 4; i++) {
        for (int j = 3; j >= 0; j--) {
            int x = j;
            while (x < 3 && (state[i][x + 1] == 0 || state[i][x + 1] == state[i][x]) && state[i][x] != 0) {
                if (state[i][x + 1] == state[i][x]) {
                    state[i][x + 1] *= 2;
                } else {
                    state[i][x + 1] = state[i][x];
                }
                state[i][x] = 0;
                x++;
                moved = true;
            }
        }
    }
    return moved;
}

vector<pair<int, vector<vector<int>>>> permutations(vector<vector<int>> &state) {
    vector<pair<int, vector<vector<int>>>> allStates;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (state[i][j] == 0) {
                vector<vector<int>> temp = state;
                temp[i][j] = 2;
                allStates.emplace_back(2, temp);
                temp[i][j] = 4;
                allStates.emplace_back(4, temp);
            }
        }
    }
    return allStates;
}

double valueOfState(vector<vector<int>> state, int newNum) {
    double p;
    p = (newNum == 2) ? 0.9 : 0.1;
    double totalValue;
    double zeroes = 0;
    double mergePotential = 0;
    double sum = 0;
    int max = 0;
    pair<int, int> maxLocation;
    vector<vector<int>> neighbors = {{0,  1},
                                     {1,  0},
                                     {0,  -1},
                                     {-1, 0}};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            sum += state[i][j];
            if (state[i][j] == 0) zeroes++;
            if (state[i][j] >= max) {
                max = state[i][j];
                maxLocation = {i, j};
            }
            for (int l = 0; l < 4; l++) {
                int x = i + neighbors[l][0];
                int y = j + neighbors[l][1];
                if (x < 4 && x >= 0 && y < 4 && y >= 0) {
                    if (state[i][j] == state[x][y] && state[i][j] != 0) {
                        mergePotential += log2(state[i][j]) / 2;
                    }
                }
            }
        }
    }
    totalValue = ((sum / 2) * zeroes) + ((sum / 4) * mergePotential) + (log2(max) * (sum / 10));
    int x = maxLocation.first;
    int y = maxLocation.second;
    totalValue *= maxValueLocationBoost(x, y);
    return (p * totalValue);
}

double maxValueLocationBoost(int x, int y) {
    double modifier = 1;
    if ((x == 0 && y == 0) || (x == 0 && y == 3) || (x == 3 && y == 0) || (x == 3 && y == 3)) {
        modifier = 1.8;
    }
    if ((x == 1 && y == 0) || (x == 0 && y == 1) || (x == 0 && y == 2) || (x == 1 && y == 3) ||
        (x == 2 && y == 3) || (x == 3 && y == 2) || (x == 3 && y == 1) || (x == 2 && y == 0)) {
        modifier = 1.3;
    }
    return modifier;
}