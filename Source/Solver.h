#ifndef __Sudoku__SOLVER
#define __Sudoku__SOLVER

#include "Header.h"
#include "Grille.h"
#include "Possibilities.h"

class Solver {

public:
	Solver();
    Solver(Grille *grille);
    void initiate();
	void update(int, int, int);

	int *hint();
	int *hintHuman();
	bool isHintable();
	Possibilities getPossibilities(int, int);
	static void calcPoss(NineUplet const region, NineUplet const line, NineUplet const column, Possibilities &p);
	int Solver::hintHumanInNuple(NineUplet nuple, int value);

private:
	Grille *grid;
	bool initiated = false;
	list<Possibilities> leftPossibilities;
	bool hintable;
};
#endif
