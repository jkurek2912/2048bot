#include "bot.h"
#include "helpers.h"
#include "utils.h"

char getRandomDirection() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int randomNumber = rand() % 4;
    switch(randomNumber) {
        case 0:
            return 'w'; // Up
        case 1:
            return 's'; // Down
        case 2:
            return 'a'; // Left
        case 3:
            return 'd'; // Right
    }
}

char findBestMove(vector<vector<int>> state) {
    vector<vector<int>> w = state;
    vector<vector<int>> a = state;
    vector<vector<int>> s = state;
    vector<vector<int>> d = state;
    nextState(w, 'w');
    nextState(a, 'a');
    nextState(s, 's');
    nextState(d, 'd');
    double wScore = valueOfState(w);
    double aScore = valueOfState(a);
    double sScore = valueOfState(s);
    double dScore = valueOfState(d);
    cout << "w\n";
    printState(w);
    cout << "a\n";
    printState(a);
    cout << "s\n";
    printState(s);
    cout << "d\n";
    printState(d);
    cout << wScore << ", " << aScore << ", " << sScore << ", " << dScore << endl;
    if (wScore >= aScore && wScore >= sScore && wScore >= dScore && w != state) return 'w';
    if (aScore >= wScore && aScore >= sScore && aScore >= dScore && a != state) return 'a';
    if (sScore >= wScore && sScore >= aScore && wScore >= dScore && s != state) return 's';
    if (dScore >= wScore && dScore >= aScore && dScore >= sScore && d != state) return 'd';
    return getRandomDirection();
}

void nextState(vector<vector<int>>& state, char c) {
    if (c == 'w') {
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
                }
            }
        }
    }
    if (c == 's') {
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
                }
            }
        }
    }
    if (c == 'a') {
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
                }
            }
        }
    }
    if (c == 'd') {
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
                }
            }
        }
    }
}

double valueOfState(vector<vector<int>> state) {
    double totalValue;
    double zeroes = 0;
    double mergePotential = 0;
    int sum = 0;
    int max = 0;
    pair<int, int> maxLocation;
    vector<vector<int>> neighbors = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
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
    totalValue = ((0.7) * sum) + ((sum / 2) * zeroes) + ((sum / 4) * mergePotential) + (log2(max) * (sum / 10));
    int x = maxLocation.first;
    int y = maxLocation.second;
    if ((x == 0 && y == 0) || (x == 0 && y == 3) || (x == 3 && y == 0) || (x == 3 && y == 3)) totalValue *= 1.5;
    return totalValue;
}