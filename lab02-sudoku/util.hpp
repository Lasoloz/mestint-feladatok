#ifndef INIT_INCLUDED
#define INIT_INCLUDED

#include "globals.hpp"

// Declarations:
inline void occupy(const int x, const int y, const int boxIndex,const int val);

inline void deoccupy(
    const int x, const int y,
    const int boxIndex, const int val
);

inline int getVal(const int val);

inline bool invalidPos(
    const int x, const int y, const int boxIndex, const int val
);


// Definitions:
void occupy(const int x, const int y, const int boxIndex,const int val) {
    field[x][y] = val;
    rowOccupancy[y][val] = true;
    colOccupancy[x][val] = true;
    boxOccupancy[boxIndex][val] = true;
    ++numCount;
}

void deoccupy(
    const int x, const int y,
    const int boxIndex, const int val
) {
    rowOccupancy[y][val] = false;
    colOccupancy[x][val] = false;
    boxOccupancy[boxIndex][val] = false;
    --numCount;
}

int getVal(const int val) {
    return val + 1;
}

bool invalidPos(
    const int x, const int y, const int boxIndex, const int val
) {
    return rowOccupancy[y][val] ||
        colOccupancy[x][val] ||
        boxOccupancy[boxIndex][val];
}


#endif
