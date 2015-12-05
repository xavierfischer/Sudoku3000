

#ifndef __Sudoku__TwoOutOfThreeRowVisitor__
#define __Sudoku__TwoOutOfThreeRowVisitor__

#include <stdio.h>
#include "IVisitor.h"
#include "Grid.h"

class TwoOutOfThreeRowVisitor: public IVisitor {

public:
    TwoOutOfThreeRowVisitor();
    bool Visit(Grid &grid);
};

#endif /* defined(__Sudoku__TwoOutOfThreeRowVisitor__) */
