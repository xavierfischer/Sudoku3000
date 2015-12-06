
#ifndef __Sudoku__GRILLE__
#define __Sudoku__GRILLE__

#include <stdio.h>
#include "Header.h"
#include "Cellule.h"
#include "NineUplet.h"

class Grille {
public:
	Grille();
	Grille(int *a[9]);

	NineUplet getRegionFromCell(int, int);

	NineUplet getRegion(int, int);
	NineUplet getLine(int);
	NineUplet getColumn(int);
	Cellule getCell(int, int);
	bool isFull();
	bool isConsistent();

private: 
	Cellule cells[9][9];

};

#endif /* defined(__Sudoku__Grid__) */
