
#ifndef __Sudoku__TwoOutOfThreeColumnVisitor__
#define __Sudoku__TwoOutOfThreeColumnVisitor__

#include <stdio.h>
#include "IVisitor.h"
#include "Grid.h"

class TwoOutOfThreeColumnVisitor {

public:
    TwoOutOfThreeColumnVisitor();
    bool Visit(Grid &grid);
};

#endif /* defined(__Sudoku__TwoOutOfThreeColumnVisitor__) */
