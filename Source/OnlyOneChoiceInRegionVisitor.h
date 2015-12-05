#ifndef __Sudoku__OnlyOneChoiceInRegionVisitor__
#define __Sudoku__OnlyOneChoiceInRegionVisitor__

#include <stdio.h>
#include "IVisitor.h"
#include "LastCellFinder.h"

class OnlyOneChoiceInRegionVisitor: public IVisitor {

public:
    OnlyOneChoiceInRegionVisitor();
    bool Visit(Grid &grid);
};

#endif /* defined(__Sudoku__OnlyOneChoiceInRegionVisitor__) */
