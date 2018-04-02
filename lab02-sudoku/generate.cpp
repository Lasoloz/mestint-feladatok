#include "generate.hpp"

// int originalField[9][9];
int originalNumCount;


void generatePuzzle(const int level) {
    initialize9();
    srand(time(NULL));
    std::array<int, 9> startPerm = getRandomPerm();
    int row = rand() % 9;

    for (int x = 0; x < 9; ++x) {
        occupy(x, row, getBoxIndex9(x, row), startPerm[x]);
    }

    numCount = 9;

    if (row == 0) {
        generateFull9(0, 1, 0);
    } else {
        generateFull9(0, 0, row);
    }

    // Save original puzzle:
    btStack.push(State::copyGameState());
    originalNumCount = numCount;

    // Easy: 31->37
    takeOutNumbers(31, 38);
    if (level > 0) {
        // Medium: 23->30
        takeOutNumbers(23, 31);
        if (level > 1) {
            // Hard: 17->22
            takeOutNumbers(17, 22);
        }
    }

    fprintf(out, "Generated puzzle:\n");
    printIt9Puzzle(field);
    fprintf(out, "Solved form:\n");
    printIt9(result);
}
