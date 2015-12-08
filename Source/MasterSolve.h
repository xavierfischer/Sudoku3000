#ifndef __Sudoku__MASTERSOLVE
#define __Sudoku__MASTERSOLVE

#include "Header.h"
#include "Grille.h"
#include "Possibilities.h"
#include "Solver.h"

class MasterSolve {

public:
	MasterSolve(Grille *grille);

	bool hintComputerUnit();
	bool hintHumanUnit();

	bool solve();
	bool solveUnit();

private:
	Grille *grid;
	Solver solver;
};

#endif
