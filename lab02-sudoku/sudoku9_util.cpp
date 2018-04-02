#include "sudoku9_util.hpp"

void initialize9() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            field[i][j] = -1;
            rowOccupancy[i][j] = false;
            colOccupancy[i][j] = false;
            boxOccupancy[i][j] = false;
            for (int k = 0; k < 9; ++k) {
                numberPossibilities[i][j][k] = true;
            }
        }
    }

    solve_state = 0;

    numCount = 0;
}

bool read9(const char *fileName) {
    FILE *in = fopen(fileName, "r");
    if (in == NULL) {
        fprintf(stderr, "Failed to open file!\n");
        return false;
    }
    for (int y = 0; y < 9; ++y) {
        for (int x = 0; x < 9; ++x) {
            char inChar;

            do {
                int inVal = fgetc(in);
                if (inVal < 0) {
                    fprintf(stderr, "Failed to read character!\n");
                    return false;
                }
                inChar = (char) inVal;
            } while ((inChar < '1' || inChar > '9') && inChar != '.');

            if (inChar >= '1' && inChar <= '9') {
                if (!occupy9(x, y, inChar - '1')) {
                    fprintf(stderr, "Invalid sudoku puzzle!\n");
                    return false;
                }
            } else if (inChar == '.') {
                continue;
            } else {
                fprintf(stderr, "Invalid character!\n");
                return false;
            }
        }
    }
    if (fclose(in) < 0) {
        fprintf(stderr, "Failed to close file!\n");
        return false;
    }

    return true;
}
