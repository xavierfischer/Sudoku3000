
#ifndef __Sudoku__Cell__
#define __Sudoku__Cell__

#include <stdexcept>
#include "Header.h"
#include "Possibilities.h"

class Cellule {
public:
	Cellule();
    Cellule (int);
	int getValue();
	bool isEmpty();
	void setValue(int);
	bool fixed;
	Possibilities *getPossibilities();
	
private:
	int value;
	Possibilities possibilities;
};

#endif /* defined(__Sudoku__Cell__) */
