
#ifndef __Sudoku__TripleHolder__
#define __Sudoku__TripleHolder__

#include <stdio.h>
#include "Header.h"
#include "ValueEliminator.h"

class TripleHolder {
public:
    TripleHolder();
    TripleHolder(Cell &c1, Cell &c2, Cell &c3);
    Cell &getCell1();
    Cell &getCell2();
    Cell &getCell3();
    string value();
    void flagValues(ValueEliminator &valEliminator);
    bool isValuePresent(unsigned char iValue);
    string getString();

    Cell cell1;
    Cell cell2;
    Cell cell3;
};


#endif /* defined(__Sudoku__TripleHolder__) */
