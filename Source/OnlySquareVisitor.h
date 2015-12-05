
#ifndef __Sudoku__OnlySquareVisitor__
#define __Sudoku__OnlySquareVisitor__

#include <stdio.h>
#include "IVisitor.h"
#include "Grid.h"

class OnlySquareVisitor:public IVisitor {

public:
    OnlySquareVisitor();
    bool Visit(Grid &grid);
private:
    bool visitOnce(Grid &grid);
};

#endif /* defined(__Sudoku__OnlySquareVisitor__) */
