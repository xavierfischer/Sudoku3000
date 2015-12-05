
#ifndef __Sudoku__LastCellFinder__
#define __Sudoku__LastCellFinder__

#include <stdio.h>
#include "Header.h"
#include "TripleHolder.h"
#include "Region.h"

class LastCellFinder {

public:
    LastCellFinder();
    LastCellFinder(TripleHolder &tri1, TripleHolder &tri2, TripleHolder &tri3);
    bool fill();

private:
    TripleHolder &triplet1;
    TripleHolder &triplet2;
    TripleHolder &triplet3;
};
#endif /* defined(__Sudoku__LastCellFinder__) */
