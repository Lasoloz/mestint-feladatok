// Heim László, hlim1616, 522
#include <cstdio>

#include <vector>

#include <algorithm>


// Global structures (speed)
int base[10][10];
int numbersInUse[100];
FILE *out;
int size;
int halfSize;



// Typedefs and helpers:
void printItTRight() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            fprintf(out, "%d ", base[i][j]);
        }
        fputc('\n', out);
    }
    fputc('\n', out);
}

void printItTLeft() {
    for (int i = 0; i < size; ++i) {
        for (int j = size - 1; j >= 0; --j) {
            fprintf(out, "%d ", base[i][j]);
        }
        fputc('\n', out);
    }
    fputc('\n', out);
}

void printItBRight() {
    for (int i = size - 1; i >= 0; --i) {
        for (int j = 0; j < size; ++j) {
            fprintf(out, "%d ", base[i][j]);
        }
        fputc('\n', out);
    }
    fputc('\n', out);
}

void printItBLeft() {
    for (int i = size - 1; i >= 0; --i) {
        for (int j = size - 1; j >= 0; --j) {
            fprintf(out, "%d ", base[i][j]);
        }
        fputc('\n', out);
    }
    fputc('\n', out);
}

void printItNormal() {
    printItTRight();
}

void printItEven() {
    printItTRight();
    printItTLeft();
    printItBRight();
    printItBLeft();
}

bool symmetry = false;



// Class definitions:
class MagicBox {
    int numberUseCount;
    int sqSize;
    int helpCount;
    int helpSize;
    int magicSum;

    int resultCount;

    // Private generator functions:
    inline void initialize();

    // inline int sum(int, int, const int, iter2D) const;
    inline int rowSum(int, int, const int) const;
    inline int colSum(int, int, const int) const;
    inline int diag1Sum(int, int, const int) const;
    inline int diag2Sum(int, int, const int) const;
    inline void useNumber(const int, const int, const int);
    inline void backtrackTry(const int, const int, const int);
    inline void backtrack(const int, const int);

    // Private printing method:
    inline void printIt() const;

public:
    void generate();
};


// Private methods:
// Initialization:
inline void MagicBox::initialize() {

    sqSize = size * size;
    magicSum = size * (1 + sqSize) / 2;
    helpCount = (size - 1) * size - 2;
    helpSize = size - 1;

    // numbersInUse.resize(sqSize, false);
    numberUseCount = 0;

    resultCount = 0;
}

inline int MagicBox::rowSum(int row, int col, const int count) const {
    int s = base[row][col];
    for (int i = 1; i < count; ++i) {
        ++col;
        s += base[row][col];
    }
    return s;
}
inline int MagicBox::colSum(int row, int col, const int count) const {
    int s = base[row][col];
    for (int i = 1; i < count; ++i) {
        ++row;
        s += base[row][col];
    }
    return s;
}
inline int MagicBox::diag1Sum(int row, int col, const int count) const {
    int s = base[row][col];
    for (int i = 1; i < count; ++i) {
        ++row;
        ++col;
        s += base[row][col];
    }
    return s;
}
inline int MagicBox::diag2Sum(int row, int col, const int count) const {
    int s = base[row][col];
    for (int i = 1; i < count; ++i) {
        ++row;
        --col;
        s += base[row][col];
    }
    return s;
}

inline void MagicBox::useNumber(const int row, const int col, const int num) {
    numbersInUse[num-1] = true;
    ++numberUseCount;
    base[row][col] = num;

    if (numberUseCount == helpCount) {
        backtrackTry(
            helpSize, 0, magicSum - diag2Sum(0, helpSize, helpSize)
        );
    } else if (numberUseCount == sqSize) {
        if (rowSum(helpSize, 0, size) == magicSum) {
            if (symmetry) {
                resultCount += 4;
                printItEven();
            } else {
                ++resultCount;
                printItNormal();
            }
        }
    } else if (row == helpSize) {
        if (col == helpSize) {
            if (diag1Sum(0, 0, size) == magicSum) {
                backtrackTry(
                    row,
                    col - 1,
                    magicSum - colSum(0, col - 1, helpSize)
                );
            }
        } else if (col == 0) {
            backtrackTry(
                row - 1,
                col,
                magicSum - colSum(0, 0, size - 2) - base[helpSize][0]
            );
        } else {
            backtrackTry(
                row, col - 1, magicSum - colSum(0, col - 1, helpSize)
            );
        }
    } else if (col == 0) {
        backtrackTry(
            row, helpSize, magicSum - rowSum(row, 0, helpSize)
        );
    } else if (col == helpSize) {
        if (row == size - 2) {
            backtrackTry(
                row + 1, col, magicSum - colSum(0, col, helpSize)
            );
        } else {
            backtrack(row + 1, col - 1);
        }
    } else {
        backtrack(row, col - 1);
    }

    // base[row][col] = 0;
    --numberUseCount;
    numbersInUse[num-1] = false;
}


inline void MagicBox::backtrackTry(
    const int row, const int col, const int expected
) {
    if (numbersInUse[expected - 1] || expected < 1 || expected > sqSize) {
        return;
    }
    if (symmetry && expected == 1 && (col > halfSize || row > halfSize)) {
        return;
    }

    useNumber(row, col, expected);
}


inline void MagicBox::backtrack(const int row, const int col) {
    if (symmetry && (col > halfSize || row > halfSize)) {
        for (int i = 1; i < sqSize; ++i) {
            if (numbersInUse[i]) {
                continue;
            }

            useNumber(row, col, i + 1);
        }
    } else {
        for (int i = 0; i < sqSize; ++i) {
            if (numbersInUse[i]) {
                continue;
            }

            useNumber(row, col, i + 1);
        }
    }
}


// Public methods:
inline void MagicBox::generate() {
    initialize();
    backtrack(0, size - 2);
    fprintf(out, "====================\nCount: %d\n", resultCount);
    fprintf(stderr, "%d", resultCount);
}



int main() {
    #ifndef USE_STREAM
    out = fopen("result.out", "w");
    if (out == NULL) {
        return 2;
    }
    #else
    out = stdout;
    #endif

    fprintf(stderr, "How many numbers?\n");
    if (scanf("%d", &size) < 1) {
        return 4;
    }

    if (size > 10) {
        fprintf(stderr, "Size must be less than 10!\n");
        return 4;
    }

    if (size < 3) {
        fprintf(stderr, "Size must be greater than 2!\n");
        return 1;
    }

    if (size % 2 == 0) {
        symmetry = true;
    }
    halfSize = size / 2 - 1;


    // Create magic square:
    MagicBox mb;
    mb.generate();
}
