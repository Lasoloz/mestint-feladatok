#include "sudoku9.hpp"

std::stack<State> btStack;


void initBacktrack() {
    // Find the position, where the least modification happened:
    int xpos = 0, ypos = 0;
    int possibilites = 10;
    for (int x = 0; x < 9; ++x) {
        for (int y = 0; y < 9; ++y) {
            const int possib = countNumberPossibilities(x, y);

            if (possib == 2) {
                xpos = x; ypos = y;
                break;
            } else if (possib < possibilites && possib > 2) {
                xpos = x; ypos = y;
                possibilites = possib;
            }
        }
    }

    // Backtrack:
    for (int val = 0; val < 9; ++val) {
        if (solve_state > 2/* && !needAll*/) {
            return;
        }
        if (numberPossibilities[xpos][ypos][val]) {
            btStack.push(State::copyGameState());

            occupy9_fast(xpos, ypos, getBoxIndex9(xpos, ypos), val);
            btStack.top().pushModification(xpos, ypos, val, -1);
            solve9Core();

            btStack.top().rewriteGameField();
            btStack.pop();
        }
    }
}
