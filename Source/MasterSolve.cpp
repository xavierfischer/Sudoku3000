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

				//BACKTRACK

				solver.initiate();
				list<Possibilities> leftPoss = solver.leftPossibilities;
				if (leftPoss.size() > 0) {
					Possibilities poss = leftPoss.front();
					if (poss.possibles() == 2) {
						int a = 0, b = 0;
						for (int i = 0; i < 9; i++) {
							b = (a != 0 && b == 0 && poss.getPossibility(i)) ? i + 1 : b;
							a = (a == 0 && poss.getPossibility(i)) ? i + 1 : a;
						}
						int i = poss.attachedI;
						int j = poss.attachedJ;
						Grille grilleBackTrack(*grid);
						(*grilleBackTrack.getCell(i, j)).setValue(a);
						MasterSolve backTrackSolver(&grilleBackTrack);

						(*(*grid).getCell(i, j)).setValue(backTrackSolver.solve() ? a : b);
						solver.initiate();
						return true;
					}
					else {
						return false;
					}
				}
				else {
					return false;
				}
				return false;
			}
		}
	}
	else {
		return false;
	}
}

bool MasterSolve::solve() {
	if ((*grid).isConsistent()) {
		solver.initiate();
		bool algoCanYouContinue = true;

		while (algoCanYouContinue) {
			int missingValues = (*grid).emptyValues();
			algoCanYouContinue = solveUnit();
		}

		return (*grid).isFull();
	}
	return false;
}
