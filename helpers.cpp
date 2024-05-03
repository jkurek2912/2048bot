#include "helpers.h"

void printState(vector<vector<int>> state) {
    cout << "--------------------\n";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << state[i][j] << " ";
        }
        cout << endl;
    }
    cout << "--------------------\n";
}

void getCoordinate() {
    for (;;) {
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            POINT pos;
            GetCursorPos(&pos);
            cout << "{" << pos.x << ", " << pos.y << "}, " << endl;
            Sleep(150);
        }
    }
}