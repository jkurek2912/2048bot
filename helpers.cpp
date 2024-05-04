#include "helpers.h"

vector<vector<int>> makeState() {
    vector<vector<int>> state;
    for (int i = 0; i < 4; i++) {
        vector<int> temp;
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        temp.push_back(a);
        temp.push_back(b);
        temp.push_back(c);
        temp.push_back(d);
        state.push_back(temp);
    }
    return state;
}

char getRandomDirection() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(0, 3);
    int randomNumber = distr(gen);
    switch (randomNumber) {
        case 0:
            return 'w'; // Up
        case 1:
            return 's'; // Down
        case 2:
            return 'a'; // Left
        default:
            return 'd'; // Right
    }
}
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