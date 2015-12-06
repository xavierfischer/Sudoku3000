
#ifndef __Sudoku__Cell__
#define __Sudoku__Cell__

#include <stdio.h>

class Cell {
public:
    Cell ();
    Cell(char iValue);
    bool isEmpty();
    Cell &operator=(unsigned char iValue);
    operator unsigned char() const ;
    bool operator==(unsigned char iValue) const;

    char iValue;
    int numberCell;
};

#endif /* defined(__Sudoku__Cell__) */
