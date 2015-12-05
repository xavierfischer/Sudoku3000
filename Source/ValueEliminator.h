
#ifndef __Sudoku__ValueEliminator__
#define __Sudoku__ValueEliminator__

#include <stdio.h>
#include "Header.h"
//XCode ne reconnait pas les set, donc on utilise des list a la place
class ValueEliminator {

public:
    ValueEliminator();
    void flag(unsigned char iValue);
    int availableValues();
    char availableValue();

    bool missingValues[9];
};

#endif /* defined(__Sudoku__ValueEliminator__) */
