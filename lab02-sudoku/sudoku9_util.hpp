#ifndef SUDOKU9_UTIL_INCLUDED
#define SUDOKU9_UTIL_INCLUDED

#include "globals.hpp"
#include "util.hpp"

// Declarations:
inline int getBoxIndex9(int x, int y);
inline void posInvalidate(const int x, const int y);

inline void rowInvalidate(
    const int y,
    const int x0,
    const int x1,
    const int val
);
inline void colInvalidate(
    const int x,
    const int y0,
    const int y1,
    const int val
);
inline void boxInvalidate(
    const int x0,
    const int x1,
    const int y0,
    const int y1,
    const int val
);
inline void invalidate(const int x, const int y, const int val);


inline int getBoxStart(int index);
inline int getBoxEnd(int index);

inline void occupy9_fast(
    const int x, const int y, const int boxIndex, const int val
);
inline bool occupy9(const int x, const int y, const int val);

void initialize9();
bool read9(const char *fileName);

inline void printIt9Part(const int y, const int what[9][9]);
inline void printIt9(const int what[9][9]);


inline int checkNumberPossibilities(const int x, const int y);
inline bool searchWithOnePossibility(int &xR, int &yR, int &valR);
inline int searchNumberInRow(const int y, const int val);
inline int searchNumberInCol(const int x, const int val);
inline bool searchNumbersInRows(int &xR, int &yR, int &valR);
inline bool searchNumbersInCols(int &xR, int &yR, int &valR);
inline bool searchNumberInBox(
    const int boxX, const int boxY, int &xR, int &yR, const int val
);
inline bool searchNumbersInBoxes(int &xR, int &yR, int &valR);







// Inline definitions:
inline int getBoxIndex9(int x, int y) {
    x /= 3;
    y /= 3;
    return 3 * y + x;
}

inline void posInvalidate(const int x, const int y) {
    for (int i = 0; i < 9; ++i) {
        numberPossibilities[x][y][i] = false;
    }
}

inline void rowInvalidate(
    const int y,
    const int x0,
    const int x1,
    const int val
) {
    for (int x = x0; x < x1; ++x) {
        numberPossibilities[x][y][val] = false;
    }
}

inline void colInvalidate(
    const int x,
    const int y0,
    const int y1,
    const int val
) {
    for (int y = y0; y < y1; ++y) {
        numberPossibilities[x][y][val] = false;
    }
}

inline void boxInvalidate(
    const int x0,
    const int x1,
    const int y0,
    const int y1,
    const int val
) {
    for (int x = x0; x < x1; ++x) {
        for (int y = y0; y < y1; ++y) {
            numberPossibilities[x][y][val] = false;
        }
    }
}


inline int getBoxStart(int index) {
    index /= 3;
    return index * 3;
}

inline int getBoxEnd(int index) {
    index /= 3;
    return (index + 1) * 3;
}


inline void invalidate(const int x, const int y, const int val) {
    posInvalidate(x, y);
    rowInvalidate(y, 0, getBoxStart(x), val);
    rowInvalidate(y, getBoxEnd(x), 9, val);
    colInvalidate(x, 0, getBoxStart(y), val);
    colInvalidate(x, getBoxEnd(y), 9, val);
    boxInvalidate(
        getBoxStart(x), getBoxEnd(x),
        getBoxStart(y), getBoxEnd(y),
        val
    );
}

inline void occupy9_fast(
    const int x, const int y, const int boxIndex, const int val
) {
    occupy(x, y, boxIndex, val);

    invalidate(x, y, val);
}

inline bool occupy9(const int x, const int y, const int val) {
    const int boxIndex = getBoxIndex9(x, y);
    if (invalidPos(x, y, boxIndex, val)) {
        // fprintf(stderr, "Trying to put value to wrong place!\n");
        return false;
    }

    occupy9_fast(x, y, boxIndex, val);

    return true;
}

inline void deoccupy9(const int x, const int y, const int boxIndex) {

}

inline void printIt9Part(const int y, const int what[9][9]) {
    for (int i = 0; i < 3; ++i) {
        fprintf(out, "| ");
        const int start = i * 3;
        const int end = start + 3;
        for (int x = start; x < end; ++x) {
            fprintf(out, "%d ", getVal(what[x][y]));
        }
    }
    fprintf(out, "|\n");
}

inline void printIt9(const int what[9][9]) {
    for (int i = 0; i < 3; ++i) {
        fprintf(out, "+-------+-------+-------+\n");
        const int start = i * 3;
        const int end = start + 3;
        for (int y = start; y < end; ++y) {
            printIt9Part(y, what);
        }
    }
    fprintf(out, "+-------+-------+-------+\n");
}


inline int checkNumberPossibilities(const int x, const int y) {
    int val = -1;
    for (int i = 0; i < 9; ++i) {
        if (numberPossibilities[x][y][i]) {
            if (val != -1) {
                return -1;
            }
            val = i;
        }
    }
    return val;
}


inline bool searchWithOnePossibility(int &xR, int &yR, int &valR) {
    for (int x = 0; x < 9; ++x) {
        for (int y = 0; y < 9; ++y) {
            int result = checkNumberPossibilities(x, y);
            if (result > -1) {
                xR = x;
                yR = y;
                valR = result;
                return true;
            }
        }
    }

    return false;
}


inline int searchNumberInRow(const int y, const int val) {
    int xR = -1;
    for (int x = 0; x < 9; ++x) {
        if (numberPossibilities[x][y][val]) {
            if (xR != -1) {
                return -1;
            }
            xR = x;
        }
    }
    return xR;
}

inline int searchNumberInCol(const int x, const int val) {
    int yR = -1;
    for (int y = 0; y < 9; ++y) {
        if (numberPossibilities[x][y][val]) {
            if (yR != -1) {
                return -1;
            }
            yR = x;
        }
    }
    return yR;
}

inline bool searchNumbersInRows(int &xR, int &yR, int &valR) {
    for (int y = 0; y < 9; ++y) {
        for (int val = 0; val < 9; ++val) {
            if (!rowOccupancy[y][val]) {
                continue;
            }

            const int testX = searchNumberInRow(y, val);
            if (testX != -1) {
                xR = testX;
                yR = y;
                valR = val;
                return true;
            }
        }
    }
    return false;
}

inline bool searchNumbersInCols(int &xR, int &yR, int &valR) {
    for (int x = 0; x < 9; ++x) {
        for (int val = 0; val < 9; ++val) {
            if (!colOccupancy[x][val]) {
                continue;
            }

            const int testY = searchNumberInCol(x, val);
            if (testY != -1) {
                xR = x;
                yR = testY;
                valR = val;
                return true;
            }
        }
    }
    return false;
}

inline bool searchNumberInBox(
    const int boxX, const int boxY, int &xR, int &yR, const int val
) {
    const int sx = boxX * 3; const int sxe = sx + 3;
    const int sy = boxY * 3; const int sye = sy + 3;
    bool found = false;
    for (int x = sx; x < sxe; ++x) {
        for (int y = sy; y < sye; ++y) {
            if (numberPossibilities[x][y][val]) {
                if (found) {
                    return false;
                }
                xR = x;
                yR = y;
                found = true;
            }
        }
    }
    return found;
}

inline bool searchNumbersInBoxes(int &xR, int &yR, int &valR) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int val = 0; val < 9; ++val) {
                if (!boxOccupancy[getBoxIndex9(i, j)][val]) {
                    continue;
                }

                if (searchNumberInBox(i, j, xR, yR, val)) {
                    valR = val;
                    return true;
                }
            }
        }
    }
    return false;
}

#endif
