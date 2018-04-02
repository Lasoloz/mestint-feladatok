#ifndef GLOBALS_INCLUDED
#define GLOBALS_INCLUDED

#include <array>

#include <cstdio>

// Output:
extern FILE * out;

// Generic:
extern int field[9][9];
extern bool rowOccupancy[9][9];
extern bool colOccupancy[9][9];
extern bool boxOccupancy[9][9];
extern int numCount;

// First task:
extern int results4;

// Second task:
extern bool numberPossibilities[9][9][9];
extern int solve_state;
extern int result[9][9];
extern bool needAll;

#endif
