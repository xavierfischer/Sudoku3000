#ifndef __Sudoku__MASTERSOLVE
#define __Sudoku__MASTERSOLVE

#include "Header.h"
#include "Grille.h"
#include "Possibilities.h"
#include "Solver.h"

class MasterSolve {

public:
	MasterSolve(Grille *grille);
	bool hint();
	bool solve();

private:
	Grille *grid;
	bool LastCellHint;
	Solver solver;
};

#endif
