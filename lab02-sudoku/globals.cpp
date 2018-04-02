#include "globals.hpp"

// Output:
FILE *out;

// Generic:
int field[9][9];
bool rowOccupancy[9][9];
bool colOccupancy[9][9];
bool boxOccupancy[9][9];
int numCount;

// First task:
int results4;

// Second task:
bool numberPossibilities[9][9][9];
int solve_state;
int result[9][9];
bool needAll;
