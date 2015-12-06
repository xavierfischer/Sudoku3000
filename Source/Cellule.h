
#ifndef __Sudoku__Cell__
#define __Sudoku__Cell__

#include <stdexcept>
#include "Header.h"

class Cellule {
public:
	Cellule();
    Cellule (int);
	int value;
	bool isFixed;
};

#endif /* defined(__Sudoku__Cell__) */
