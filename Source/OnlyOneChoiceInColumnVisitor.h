
#ifndef __Sudoku__OnlyOneChoiceInColumnVisitor__
#define __Sudoku__OnlyOneChoiceInColumnVisitor__

#include <stdio.h>
#include "IVisitor.h"
#include "LastCellFinder.h"

class OnlyOneChoiceInColumnVisitor: public IVisitor{
public:
    OnlyOneChoiceInColumnVisitor();
    bool Visit(Grid &grid);
};

#endif /* defined(__Sudoku__OnlyOneChoiceInColumnVisitor__) */
