
#ifndef __Sudoku__Cell__
#define __Sudoku__Cell__

#include <stdexcept>
#include "Header.h"

class Cellule {
public:
	Cellule();
    Cellule (int);
	int getValue();
	bool isEmpty();
	bool isGuess;
	bool isFixed;
	void setValue(int);
private:
	int value;
};

#endif /* defined(__Sudoku__Cell__) */
