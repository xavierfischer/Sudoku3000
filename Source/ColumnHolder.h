

#ifndef __Sudoku__ColumnHolder__
#define __Sudoku__ColumnHolder__

#include <stdio.h>
#include "Header.h"
#include "TripleHolder.h"

class ColumnHolder : public TripleHolder {
public:
    ColumnHolder();
    ColumnHolder(Cell &cTop, Cell &cCenter, Cell &cBottom);
    Cell &T();
    Cell &C();
    Cell &B();

};


#endif /* defined(__Sudoku__ColumnHolder__) */
