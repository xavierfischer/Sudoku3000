#include "MasterSolve.h"

MasterSolve::MasterSolve(Grille *grille){
	grid = grille;
	solver = Solver(grille);
}

bool MasterSolve::hint() {
	return false;
}

bool MasterSolve::hintHuman() {
	int *result = solver.hintHuman();
	int i = result[0];
	int j = result[1];
	int value = result[2];
	return value == 0;
}

bool MasterSolve::solve() {

	solver.initiate();

	while (solver.isHintable()) {
		int *result = solver.hint();
		int i = result[0];
		int j = result[1];
		int value = result[2]; // realValue
		if (value != 0) {
			solver.update(i, j, value);
		}
	}

	return (*grid).isFull() && (*grid).isConsistent();
}
