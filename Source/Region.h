

#ifndef __Sudoku__Region__
#define __Sudoku__Region__

#include <stdio.h>
#include "Header.h"
#include "Cell.h"

class Region {
public:
    Region();
    Region(string sNumbers, bool byColumn=false);
    std::list<Cell> numbers;
    bool isFull();
    Region &operator=(unsigned char iValue);
    bool isConsistent();
    Cell &getCell(int);
    int numberNotEmpty();
    list<int> listOfValues();

    Cell NO;
    Cell N;
    Cell NE;
    Cell O;
    Cell C;
    Cell E;
    Cell SO;
    Cell S;
    Cell SE;
    string sValues;
};

#endif /* defined(__Sudoku__Region__) */
