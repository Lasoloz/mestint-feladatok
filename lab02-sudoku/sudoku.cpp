#include <cstdio>

#include <string>

#include "util.hpp"
#include "globals.hpp"
#include "sudoku4.hpp"
#include "sudoku9_util.hpp"
#include "sudoku9.hpp"
#include "generate.hpp"


// Second task:
// ============================================================================
void solve9() {
    printIt9(field);
    fprintf(out, "Current number count: %d\n", numCount);
    btStack.push(State::copyGameState());
    solve9Core();
    if (solve_state == 0) {
        fprintf(stderr, "The puzzle cannot be solved!\n");
    } else if (solve_state > 1) {
        fprintf(stderr, "Multiple solutions!\n");
        // fprintf(stderr, "Result count: %d\n", solve_state);
        fprintf(out, "One solution:\n");
        printIt9(result);
    } else {
        printIt9(result);
    }
}



// Main function:
int main(int argc, char **argv) {
    // Read option:
    int opt = 0;
    if (argc == 1) {
        opt = 0;
    } else if (argc == 3) {
        std::string a(argv[1]);
        if (a == "-i") {
            opt = 1;
        } else if (a == "-g") {
            opt = 2;
        }
    } else {
        fprintf(stderr, "Not enough, or too much parameters!\n");
        return 1;
    }

    // Output:
    out = stdout;

    // Choose path:
    switch (opt) {
    case 0:
        initialize4();
        generate4(0, 0);
        fprintf(out, "Number of 4x4(2x2) sudokus: %d\n", results4);
        break;
    case 1:
        initialize9();
        if (!read9(argv[2])) {
            return 3;
        }
        needAll = true;
        solve9();
        break;
    case 2:
        fprintf(out, "Generating puzzle...\n");
        needAll = false;
        generatePuzzle(std::atoi(argv[2]));
        break;
    default:
        fprintf(stderr, "Invalid option!\n");
    }
}
