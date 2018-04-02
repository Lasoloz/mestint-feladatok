#include "sudoku4.hpp"

void initialize4() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            field[i][j] = -1;
            rowOccupancy[i][j] = false;
            colOccupancy[i][j] = false;
            boxOccupancy[i][j] = false;
        }
    }

    numCount = 0;
    results4 = 0;
}

void generate4(const int x, const int y) {
    for (int i = 0; i < 4; ++i) {
        const int boxIndex = getBoxIndex4(x, y);
        if (invalidPos(x, y, boxIndex, i)) {
            continue;
        }

        occupy(x, y, boxIndex, i);

        if (numCount == 16) {
            printIt4();
            ++results4;
        } else if (x == 3) {
            generate4(0, y + 1);
        } else {
            generate4(x + 1, y);
        }

        deoccupy(x, y, boxIndex, i);
    }
}
