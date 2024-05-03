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

vector<vector<int>> coordinates = {{726, 371},
                                   {852, 376},
                                   {969, 375},
                                   {1092, 377},
                                   {730, 494},
                                   {853, 495},
                                   {966, 496},
                                   {1092, 497},
                                   {727, 617},
                                   {849, 619},
                                   {970, 616},
                                   {1093, 616},
                                   {724, 736},
                                   {845, 736},
                                   {967, 736},
                                   {1089, 738}};

COLORREF getPixelColor(int x, int y) {
    HDC hdc = GetDC(NULL);
    COLORREF color = GetPixel(hdc, x, y);
    ReleaseDC(NULL, hdc);
    return color;
}

void openWebsite(const char *url) {
    ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
}

void sendKeystrokes(const char key) {
    SHORT keyCode = VkKeyScanA(key);
    keybd_event(keyCode, 0, 0, 0);
    keybd_event(keyCode, 0, KEYEVENTF_KEYUP, 0);
}

void startGame() {
    const char* url = "https://play2048.co/";
    openWebsite(url);
    Sleep(1000);
    string input;
    cout << "press enter to start...";
    getline(cin, input);
    cout << "select the game window\n";
    Sleep(2000);
}

// Gets the tile value given a coordinate
int tileValue(vector<int> p) {
    COLORREF color = getPixelColor(p[0], p[1]);
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
vector<vector<int>> createStateVector() {
    vector<vector<int>> res;
    vector<int> temp;
    for (int i = 0; i < coordinates.size(); i++) {
        temp.push_back(tileValue(coordinates[i]));
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
    cout << "game over\n";
    return true;
}
