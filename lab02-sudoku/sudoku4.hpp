#ifndef SUDOKU_4_INCLUDED
#define SUDOKU_4_INCLUDED

#include <cstdio>

#include "globals.hpp"
#include "util.hpp"

// Declarations:
void initialize4();

inline int getBoxIndex4(int x, int y);

inline void printIt4Part(const int y);
inline void printIt4();

void generate4(const int x, const int y);



// Inline definitions:
int getBoxIndex4(int x, int y) {
    x /= 2;
    y /= 2;
    return 2 * y + x;
}

void printIt4Part(const int y) {
    fprintf(out, "| ");
    for (int x = 0; x < 2; ++x) {
        fprintf(out, "%d ", getVal(field[x][y]));
    }
    fprintf(out, "| ");
    for (int x = 2; x < 4; ++x) {
        fprintf(out, "%d ", getVal(field[x][y]));
    }
    fprintf(out, "|\n");

}

void printIt4() {
    fprintf(out, "/------------\\\n");
    for (int y = 0; y < 2; ++y) {
        printIt4Part(y);
    }
    fprintf(out, "|-----+-----|\n");
    for (int y = 2; y < 4; ++y) {
        printIt4Part(y);
    }
    fprintf(out, "\\-----------/\n\n");
}

#endif
