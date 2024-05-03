#include "utils.h"
#include "helpers.h"

using namespace std;

int main() {
    startGame();
    vector<vector<int>> state = createStateVector();
    cout << "playing...\n";
    while (!isDead(state)) {
        //char c = findBestMove(state);
        sendKeystrokes('w');
        sendKeystrokes('a');
        sendKeystrokes('s');
        sendKeystrokes('d');
        state = createStateVector();
    }
}
