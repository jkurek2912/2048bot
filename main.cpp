#include "utils.h"
#include "helpers.h"
#include "bot.h"

using namespace std;

int main() {
    startGame();
    vector<vector<int>> state = createStateVector();
    cout << "playing...\n";
    while (!isDead(state)) {
        char c = findBestMove(state);
        state = createStateVector();
    }
}
