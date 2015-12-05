

#ifndef __Sudoku__RowHolder__
#define __Sudoku__RowHolder__

#include <stdio.h>
#include "Header.h"
#include "TripleHolder.h"

class RowHolder : public TripleHolder {
public:
    RowHolder();
    RowHolder(Cell &cLeft, Cell &cCenter, Cell &cRight);
    Cell &G();
    Cell &C();
    Cell &D();
    string printRow();

};

#endif /* defined(__Sudoku__RowHolder__) */
