
#ifndef __Sudoku__RegionHolder__
#define __Sudoku__RegionHolder__

#include <stdio.h>
#include "Header.h"
#include "Region.h"
#include "RowHolder.h"
#include "ColumnHolder.h"
//#include "ValueEliminator.h"

class RegionHolder {
public:
    RegionHolder();
    RegionHolder(Region &region);
    Cell &NO();
    Cell &N();
    Cell &NE();
    Cell &O();
    Cell &C();
    Cell &E();
    Cell &SO();
    Cell &S();
    Cell &SE();
    RowHolder TopRow();
    RowHolder MiddleRow();
    RowHolder BottomRow();
    ColumnHolder LeftColumn();
    ColumnHolder MiddleColumn();
    ColumnHolder RightColumn();
    void flagValues(ValueEliminator &valEliminator);
    bool isValuePresent(unsigned char iValue);
    bool isFull();
    string getString();

    std::list<Cell*> cells;
    list<Cell*>::iterator iter;
};

#endif /* defined(__Sudoku__RegionHolder__) */
