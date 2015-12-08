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
	//void update(int, int, int);

	int *hintComputer();
	int *hintHuman();
	bool isHintableComputer();
	bool isHintableHuman();
	Possibilities getPossibilities(int, int);
	static void calcPoss(NineUplet const region, NineUplet const line, NineUplet const column, Possibilities &p);
	int Solver::hintHumanInNuple(NineUplet nuple, int value);
	bool initiated = false;

private:
	Grille *grid;
	list<Possibilities> leftPossibilities;
	bool hintableComputer;
	bool hintableHuman;
};
#endif
