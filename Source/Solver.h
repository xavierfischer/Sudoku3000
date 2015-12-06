#ifndef __Sudoku__LastCellFinder__
#define __Sudoku__LastCellFinder__

#include "Header.h"
#include "Grille.h"

class Solver {

public:
    Solver(Grille);
    void initiate();
	void update(int, int);
	void humanSolve();
private:
	Grille grid;
	bool possibilities [9][9][9];
	bool initiated = false;
};
#endif /* defined(__Sudoku__LastCellFinder__) */
