#ifndef SUDOKU9_INCLUDED
#define SUDOKU9_INCLUDED

#include <array>
#include <vector>
#include <stack>

#include "globals.hpp"
#include "util.hpp"
#include "sudoku9_util.hpp"

// Type definitions:
struct Position {
    int x, y;
    int val, oldVal;

    inline Position(
        const int _x, const int _y, const int _val, const int _oldVal
    ) : x(_x), y(_y), val(_val), oldVal(_oldVal) {}
};

class State {
    std::vector<Position> modifications;
    std::array<std::array<std::array<int, 9>, 9>, 9> oldNumberPossibilities;

    inline State() {};

public:
    static inline State copyGameState() {
        State state;

        for (int x = 0; x < 9; ++x) {
            for (int y = 0; y < 9; ++y) {
                for (int val = 0; val < 9; ++val) {
                    state.oldNumberPossibilities[x][y][val] =
                        numberPossibilities[x][y][val];
                }
            }
        }

        return state;
    }

    inline void rewriteGameField() {
        for (Position &pos : modifications) {
            deoccupy(pos.x, pos.y, getBoxIndex9(pos.x, pos.y), pos.val);
            field[pos.x][pos.y] = pos.oldVal;
        }

        for (int x = 0; x < 9; ++x) {
            for (int y = 0; y < 9; ++y) {
                for (int val = 0; val < 9; ++val) {
                    numberPossibilities[x][y][val] =
                        oldNumberPossibilities[x][y][val];
                }
            }
        }

        modifications.clear();
    }

    inline void pushModification(
        const int x, const int y, const int val, const int oldVal
    ) {
        modifications.push_back(Position(x, y, val, oldVal));
    }
};


// Global variables:
extern std::stack<State> btStack;


// Function declarations
inline int countNumberPossibilities(const int x, const int y);
inline void solve9Core();

void initBacktrack();


// Function definitions:
int countNumberPossibilities(const int x, const int y) {
    int count = 0;
    for (int val = 0; val < 9; ++val) {
        if (numberPossibilities[x][y][val]) {
            ++count;
        }
    }
    return count;
}


void solve9Core() {
    int oldNumCount = numCount;
    do {
        oldNumCount = numCount;

        int x, y, val;

        if (searchWithOnePossibility(x, y, val)) {
            occupy9_fast(x, y, getBoxIndex9(x, y), val);
            btStack.top().pushModification(x, y, val, -1);
        } else if (searchNumbersInRows(x, y, val)) {
            occupy9_fast(x, y, getBoxIndex9(x, y), val);
            btStack.top().pushModification(x, y, val, -1);
        } else if (searchNumbersInCols(x, y, val)) {
            occupy9_fast(x, y, getBoxIndex9(x, y), val);
            btStack.top().pushModification(x, y, val, -1);
        } else if (searchNumbersInBoxes(x, y, val)) {
            occupy9_fast(x, y, getBoxIndex9(x, y), val);
            btStack.top().pushModification(x, y, val, -1);
        } else {
            initBacktrack();
        }
    } while (oldNumCount != numCount && numCount < 81);

    if (numCount == 81) {
        if (solve_state == 0) {
            // Save result:
            for (int x = 0; x < 9; ++x) {
                for (int y = 0; y < 9; ++y) {
                    result[x][y] = field[x][y];
                }
            }
        }

        ++solve_state;
    }
}

#endif
