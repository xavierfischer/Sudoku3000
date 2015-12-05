

#ifndef __Sudoku__OnlyOneChoiceInRowVisitor__
#define __Sudoku__OnlyOneChoiceInRowVisitor__

#include <stdio.h>
#include "IVisitor.h"
#include "LastCellFinder.h"

class OnlyOneChoiceInRowVisitor: public IVisitor {

public:
    OnlyOneChoiceInRowVisitor();
    bool Visit(Grid &grid);
};

#endif /* defined(__Sudoku__OnlyOneChoiceInRowVisitor__) */
