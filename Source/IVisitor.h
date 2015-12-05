
#ifndef __Sudoku__IVisitor__
#define __Sudoku__IVisitor__

#include <stdio.h>
#include "Grid.h"

class IVisitor {

public:
    IVisitor(){}
    bool Visit(Grid &ioGrid) const;
};

#endif /* defined(__Sudoku__IVisitor__) */
