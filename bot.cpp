#include "bot.h"

char findBestMove(vector<vector<int>> state) {

}

vector<vector<int>> generateStates(vector<vector<int>> state) {

}

int valueOfState(vector<vector<int>> state) {
    int value = 0;
    int max = 0;
    pair<int, int> maxLocation;
    vector<vector<int>> neighbors = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (state[i][j] == 0) value++;
            if (state[i][j] > max) {
                max = state[i][j];
                maxLocation = {i, j};
            }
            for (int l = 0; l < 4; l++) {
                int x = i + neighbors[l][0];
                int y = j + neighbors[l][1];
                if (x < 4 && x >= 0 && y < 4 && y >= 0) {
                    if (state[i][j] == state[x][y]) {
                        value += log2(state[i][j]);
                    }
                }
            }
        }
    }
    int x = maxLocation.first;
    int y = maxLocation.second;
    if ((x == 0 && y == 0) || (x == 0 && y == 3) || (x == 3 && y == 0) || (x == 3 && y == 3)) value += 10;
    return value;
}