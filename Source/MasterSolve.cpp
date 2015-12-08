#include "MasterSolve.h"

MasterSolve::MasterSolve(Grille *grille){
	grid = grille;
	solver = Solver(grille);
}

bool MasterSolve::hintHumanUnit() {
	int *result = solver.hintHuman();
	int i = result[0];
	int j = result[1];
	int value = result[2]; // realValue
	if (value != 0) {
		(*(*grid).getCell(i, j)).setValue(value);
		solver.initiate();
		return true;
	}
	return false;
}

bool MasterSolve::hintComputerUnit() {
	int *result = solver.hintComputer();
	int i = result[0];
	int j = result[1];
	int value = result[2]; // realValue
	if (value != 0) {
		(*(*grid).getCell(i, j)).setValue(value);
		solver.initiate();
		return true;
	}
	return false;
}

bool MasterSolve::solveUnit() {
	if ((*grid).isConsistent()) {
		if (!solver.initiated) {
			solver.initiate();
		}

		if (hintHumanUnit()) {
			solver.initiate();
			return true;
		}
		else {
			if (hintComputerUnit()) {
				solver.initiate();
				return true;
			}
			else {
				return false;
			}
		}
	}
	else {
		return false;
	}
}

bool MasterSolve::solve() {

	solver.initiate();
	bool algoCanYouContinue = true;

	while (algoCanYouContinue) {
		int missingValues = (*grid).emptyValues();
		algoCanYouContinue = solveUnit();
	}

	return (*grid).isFull() && (*grid).isConsistent();
}
