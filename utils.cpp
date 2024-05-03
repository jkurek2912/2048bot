#include "utils.h"

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

void printState(std::vector<std::vector<int>> state) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << state[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void startGame() {
    const char* url = "https://play2048.co/";
    openWebsite(url);
    Sleep(1000);
    std::string input;
    std::cout << "press enter to start...";
    std::getline(std::cin, input);
    std::cout << "select the tiles";
}
