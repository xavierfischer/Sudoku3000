
#ifndef __Sudoku__NINENUPLET__
#define __Sudoku__NINENUPLET__

#include <stdio.h>
#include "Header.h"
#include "Cellule.h"

class NineUplet {
public:
	NineUplet(Cellule *a[9]);
	bool isConsistent() const;
	Cellule **getCells(); 
	bool isPresent(int n) const;
	bool isFull() const;
	Cellule *getCell(int) const;
private:
	Cellule *cells[9];
};

#endif /* defined(__Sudoku__Grid__) */
