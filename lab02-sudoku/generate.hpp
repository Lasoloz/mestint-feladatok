#ifndef GENERATE_INCLUDED
#define GENERATE_INCLUDED

#include <algorithm>
#include <array>
#include <cstdlib>

#include "globals.hpp"
#include "util.hpp"
#include "sudoku9.hpp"
#include "sudoku9_util.hpp"


// Extern variables:
// extern int originalField[9][9];
extern int originalNumCount;

// Function declarations:
inline std::array<int, 9> getRandomPerm();
inline bool generateFull9(const int x, const int y, int row);

inline void resetNumberPossibilities();
inline void revalidateFields();
inline void takeOutNumbers(const int minNumber, const int maxNumber);

inline void printIt9Puzzle(const int field[9][9]);


void generatePuzzle(const int level);


// Function defitions:
std::array<int, 9> getRandomPerm() {
    std::array<int, 9> result;
    for (int i = 0; i < 9; ++i) {
        result[i] = i;
    }

    std::random_shuffle(result.begin(), result.end());
    return result;
}

bool generateFull9(int x, int y, int row) {
    for (int val = 0; val < 9; ++val) {
        const int boxIndex = getBoxIndex9(x, y);
        if (invalidPos(x, y, boxIndex, val)) {
            continue;
        }

        occupy(x, y, boxIndex, val);

        if (numCount == 81) {
            return true;
        } else if (x == 8) {
            if (y == row - 1) {
                if (generateFull9(0, y + 2, row)) {
                    return true;
                }
            } else {
                if (generateFull9(0, y + 1, row)) {
                    return true;
                }
            }
        } else {
            if (generateFull9(x + 1, y, row)) {
                return true;
            }
        }

        deoccupy(x, y, boxIndex, val);
    }

    return false;
}


void resetNumberPossibilities() {
    for (int x = 0; x < 9; ++x) {
        for (int y = 0; y < 9; ++y) {
            for (int val = 0; val < 9; ++val) {
                numberPossibilities[x][y][val] = true;
            }
        }
    }
}

void revalidateFields() {
    resetNumberPossibilities();
    for (int x = 0; x < 9; ++x) {
        for (int y = 0; y < 9; ++y) {
            const int val = field[x][y];
            if (val >= 0) {
                invalidate(x, y, val);
            }
        }
    }
}


void printIt9Puzzle(const int field[9][9]) {
    for (int y = 0; y < 9; ++y) {
        for (int x = 0; x < 9; ++x) {
            const int val = field[x][y] + 1;
            if (val == 0) {
                fputc('.', out);
            } else {
                fputc(val + '0', out);
            }
        }
        fputc('\n', out);
    }
}


void takeOutNumbers(const int minCount, const int maxCount) {
    int tries = 0;
    do {
        btStack.top().rewriteGameField();
        numCount = originalNumCount;
        const int finalNum = rand() % (maxCount - minCount) + minCount;
        const int numsToTakeOut = originalNumCount - finalNum;

        int numsTakenOut = 0;

        while (numsTakenOut < numsToTakeOut) {
            // Find a correct number, which can be taken out:
            int x, y;
            do {
                x = rand() % 9;
                y = rand() % 9;
            } while (field[x][y] < 0);

            const int oldVal = field[x][y];
            btStack.top().pushModification(x, y, -1, oldVal);
            deoccupy(x, y, getBoxIndex9(x, y), oldVal);
            field[x][y] = -1;

            ++numsTakenOut;
        }

        // printIt9(field);

        revalidateFields();

        solve_state = 0;
        btStack.push(State::copyGameState());
        solve9Core();
        // fprintf(stderr, "Solve state: %d\n\n", solve_state);
        btStack.top().rewriteGameField();
        btStack.pop();
        ++tries;
    } while (solve_state != 1);

    originalNumCount = numCount;
    btStack.push(State::copyGameState());
}

#endif
