#include <cstdio>

#include <vector>

#include <algorithm>

// Typedefs:
typedef void (*iter2D)(int &, int &);

// Other helpers:
iter2D rowHelper = [](int &row, int &col) { ++col; };
iter2D colHelper = [](int &row, int &col) { ++row; };
iter2D diag1helper = [](int &row, int &col) { ++row; ++col; };
iter2D diag2helper = [](int &row, int &col) { ++row; --col; };



// Class definitions:
class MagicBox {
    std::vector<std::vector<int> > base;
    std::vector<int> numbersInUse;
    int numberUseCount;
    int size;
    int sqSize;
    int helpCount;
    int magicSum;
    FILE *out;

    int resultCount;

    // Private generator functions:
    inline void initialize(FILE *, const int);

    inline int sum(int, int, const int, iter2D) const;
    inline void useNumber(const int, const int, const int);
    inline void backtrackTry(const int, const int, const int);
    inline void backtrack(const int, const int);

    // Private printing method:
    inline void printIt() const;

public:
    void generate(FILE *, const int);
};


// Private methods:
// Initialization:
inline void MagicBox::initialize(FILE *out, const int size) {
    base.resize(size);
    for (int i = 0; i < size; ++i) {
        base[i].resize(size, 0);
    }

    this->size = size;
    sqSize = size * size;
    magicSum = size * (1 + sqSize) / 2;
    helpCount = (size - 1) * size - 2;

    numbersInUse.resize(sqSize, false);
    numberUseCount = 0;

    resultCount = 0;

    this->out = out;
}


// Checks:
inline int MagicBox::sum(
    int row,
    int col,
    const int count,
    iter2D iter
) const {
    int s = base[row][col];
    for (int i = 1; i < count; ++i) {
        iter(row, col);
        s += base[row][col];
    }

    return s;
}

inline void MagicBox::useNumber(const int row, const int col, const int num) {
    numbersInUse[num-1] = true;
    ++numberUseCount;
    base[row][col] = num;

    // printIt();

    if (numberUseCount == helpCount) {
        backtrackTry(
            size - 1, 0, magicSum - sum(0, size - 1, size - 1, diag2helper)
        );
    } else if (numberUseCount == sqSize) {
        if (sum(size - 1, 0, size, rowHelper) == magicSum) {
            ++resultCount;
            printIt();
        }
    } else if (row == size - 1) {
        if (col == size - 1) {
            if (sum(0, 0, size, diag1helper) == magicSum) {
                backtrackTry(
                    row,
                    col - 1,
                    magicSum - sum(0, col - 1, size - 1, colHelper)
                );
            }
        } else if (col == 0) {
            backtrackTry(
                row - 1,
                col,
                magicSum - sum(0, 0, size - 2, colHelper) - base[size - 1][0]
            );
        } else {
            backtrackTry(
                row, col - 1, magicSum - sum(0, col - 1, size - 1, colHelper)
            );
        }
    } else if (col == 0) {
        backtrackTry(
            row, size - 1, magicSum - sum(row, 0, size - 1, rowHelper)
        );
    } else if (col == size - 1) {
        if (row == size - 2) {
            backtrackTry(
                row + 1, col, magicSum - sum(0, col, size - 1, colHelper)
            );
        } else {
            backtrack(row + 1, col - 1);
        }
    } else {
        backtrack(row, col - 1);
    }

    base[row][col] = 0;
    --numberUseCount;
    numbersInUse[num-1] = false;
}


inline void MagicBox::backtrackTry(
    const int row, const int col, const int expected
) {
    if (numbersInUse[expected - 1] || expected < 1 || expected > sqSize) {
        return;
    }

    useNumber(row, col, expected);
}


inline void MagicBox::backtrack(const int row, const int col) {
    for (int i = 0; i < sqSize; ++i) {
        if (numbersInUse[i]) {
            continue;
        }

        useNumber(row, col, i + 1);
    }
}



// Printing method:
inline void MagicBox::printIt() const {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            fprintf(out, "%d ", base[i][j]);
        }
        fputc('\n', out);
    }
    fputc('\n', out);
    // fprintf(out, " current count: %d\n", resultCount);
}


// Public methods:
inline void MagicBox::generate(FILE *out, const int size) {
    initialize(out, size);
    backtrack(0, size - 2);
    fprintf(out, "====================\nCount: %d\n", resultCount);
}



int main() {
    FILE *out;
    #ifndef USE_STREAM
    out = fopen("result.out", "w");
    if (out == NULL) {
        return 2;
    }
    #else
    out = stdout;
    #endif

    fprintf(stderr, "How many numbers?\n");
    int size = 3;
    if (scanf("%d", &size) < 1) {
        return 4;
    }

    if (size < 3) {
        fprintf(stderr, "Size must be greater than 2!\n");
        return 1;
    }


    // Create magic square:
    MagicBox mb;
    mb.generate(out, size);
}
