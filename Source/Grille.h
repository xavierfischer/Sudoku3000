
#ifndef __Sudoku__GRILLE__
#define __Sudoku__GRILLE__

#include <stdio.h>
#include "Header.h"
#include "Region.h"
#include "RegionHolder.h"
#include "Cellule.h"
#include "NineUplet.h"

class Grille {
public:
	Grille();
	Grille(int *a[9]);

	NineUplet getRegion(int, int);
	NineUplet getLine(int, int);
	NineUplet getColumn(int, int);

	NineUplet getRegion(int);
	NineUplet getLine(int);
	NineUplet getColumn(int);

	bool isFull();
	bool isConsistent();

private: 
	Cellule cells[9][9];

};

#endif /* defined(__Sudoku__Grid__) */
