#include <cstdio>

#include <vector>

#include <algorithm>

// Typedefs:
typedef int utype;
typedef utype (*iterFunc)(const utype);
typedef bool (*compFunc)(const utype, const utype);
typedef void (*iter2D)(utype &, utype &);

// Print helpers:
iterFunc plusOne = [](const utype i) { return i + 1; };
iterFunc minusOne = [](const utype i) { return i - 1; };
compFunc checkPos = [](const utype idx, const utype b) { return idx <= b; };
compFunc checkNeg = [](const utype idx, const utype b) { return idx >= b; };
// Other helpers:
iter2D rowHelper = [](utype &row, utype &col) { ++col; };
iter2D colHelper = [](utype &row, utype &col) { ++row; };
iter2D diag1helper = [](utype &row, utype &col) { ++row; ++col; };
iter2D diag2helper = [](utype &row, utype &col) { ++row; --col; };



// Class definitions:
class MagicBox {
    std::vector<std::vector<utype> > base;
    std::vector<utype> numbersInUse;
    utype numberUseCount;
    utype size;
    utype sqSize;
    utype helpSize;
    utype magicSum;
    FILE *out;

    utype resultCount;

    // Private generator functions:
    void initialize(FILE *, const utype);

    utype sum(utype, utype, const utype, iter2D) const;
    void useNumber(const utype, const utype, const utype);
    void backtrackTry(const utype, const utype, const utype);
    void backtrack(const utype, const utype);

    // Private printing method:
    inline void printHelper(
        const utype, const utype, iterFunc, iterFunc, compFunc, compFunc
    ) const;
    inline void printIt() const;

public:
    void generate(FILE *, const utype);
};


// Private methods:
// Initialization:
void MagicBox::initialize(FILE *out, const utype size) {
    base.resize(size);
    // // TODO: Maybe should optimize with standard `for` ✓
    // for_each(base.begin(), base.end(), [size](std::vector<utype> elem) {
    //     elem.resize(size, 0);
    // });
    for (utype i = 0; i < size; ++i) {
        base[i].resize(size, 0);
    }

    this->size = size;
    sqSize = size * size;
    magicSum = size * (1 + sqSize) / 2;
    helpSize = (size + 1) / 2;

    numbersInUse.resize(sqSize, false);
    numberUseCount = 0;

    resultCount = 0;

    this->out = out;
}


// Checks:
utype MagicBox::sum(
    utype row,
    utype col,
    const utype count,
    iter2D iter
) const {
    utype s = base[row][col];
    for (utype i = 1; i < count; ++i) {
        iter(row, col);
        s += base[row][col];
    }

    return s;
}

void MagicBox::useNumber(const utype row, const utype col, const utype num) {
    numbersInUse[num-1] = true;
    ++numberUseCount;
    base[row][col] = num;

    // printIt();

    if (
        numberUseCount == sqSize &&
        sum(0, size - 1, size, diag2helper) == magicSum &&
        sum(size - 1, 0, size, rowHelper) == magicSum
    ) {
        ++resultCount;
        printIt();
    } else if (row == size - 1) {
        if (col == size - 1) {
            if (sum(0, 0, size, diag1helper) == magicSum) {
                backtrackTry(
                    row,
                    col - 1,
                    magicSum - sum(0, col - 1, size - 1, colHelper)
                );
            }
        } else {
            backtrackTry(
                row, col - 1, magicSum - sum(0, col - 1, size - 1, colHelper)
            );
        }
    } else if (col == size - 1) {
        if (row == size - 2) {
            backtrackTry(
                row + 1, col, magicSum - sum(0, col, size - 1, colHelper)
            );
        } else {
            backtrack(row + 1, col - 1);
        }
    } else if (col == 0) {
        backtrackTry(
            row, size - 1, magicSum - sum(row, 0, size - 1, rowHelper)
        );
    } else {
        backtrack(row, col - 1);
    }

    base[row][col] = 0;
    --numberUseCount;
    numbersInUse[num-1] = false;
}


void MagicBox::backtrackTry(
    const utype row, const utype col, const utype expected
) {
    if (numbersInUse[expected - 1] || expected < 1 || expected > sqSize) {
        return;
    }

    useNumber(row, col, expected);
}


void MagicBox::backtrack(const utype row, const utype col) {
    for (utype i = 0; i < sqSize; ++i) {
        if (numbersInUse[i]) {
            continue;
        }

        useNumber(row, col, i + 1);
    }
}



// Printing method:
inline void MagicBox::printHelper(
    const utype startPosR,
    const utype startPosC,
    iterFunc iterFuncR,
    iterFunc iterFuncC,
    compFunc compFuncR,
    compFunc compFuncC
) const {
    const utype lastR = size - 1 - startPosR;
    const utype lastC = size - 1 - startPosC;

    for (utype i = startPosR; compFuncR(i, lastR); i = iterFuncR(i)) {
        for (utype j = startPosC; compFuncC(j, lastC); j = iterFuncC(j)) {
            fprintf(out, "%d ", base[i][j]);
        }
        fputc('\n', out);
    }
    fputc('\n', out);
    // for (utype i = startPosR; compFuncR(i, lastR); i = iterFuncR(i)) {
    //     for (utype j = startPosC; compFuncC(j, lastC); j = iterFuncC(j)) {
    //         fprintf(out, "%d ", base[j][i]);
    //     }
    //     fputc('\n', out);
    // }
    // fputc('\n', out);
}
inline void MagicBox::printIt() const {
    printHelper(       0,        0,  plusOne,  plusOne, checkPos, checkPos);
    // printHelper(       0, size - 1,  plusOne, minusOne, checkPos, checkNeg);
    // printHelper(size - 1,        0, minusOne,  plusOne, checkNeg, checkPos);
    // printHelper(size - 1, size - 1, minusOne, minusOne, checkNeg, checkNeg);
}


// Public methods:
inline void MagicBox::generate(FILE *out, const utype size) {
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
    utype size = 3;
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
