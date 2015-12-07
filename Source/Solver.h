#ifndef __Sudoku__SOLVER
#define __Sudoku__SOLVER

#include "Header.h"
#include "Grille.h"
#include "Possibilities.h"

class Solver {

public:
    Solver(Grille *grille);
    void initiate();
	void update(int, int, int);

	void hint();
	bool isHintable();
	Possibilities getPossibilities(int, int);
	static void calcPoss(NineUplet const region, NineUplet const line, NineUplet const column, Possibilities &p);

private:
	Grille *grid;
	bool initiated = false;
	list<Possibilities> leftPossibilities;
	bool hintable;
};
#endif
