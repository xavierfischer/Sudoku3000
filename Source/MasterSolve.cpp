#include "MasterSolve.h"

/*
	Cette grille permet de façon simple grace à deux méthodes solve() et hint() de créer un object Solver sur une grille
	et de lancer les algorithmes. 

	Trois façons d'avancer sont implémentées : 

	Algorithme humain : regarde les cellules possibles pour une valeur donnée. S'il y a une seule cellule possible, la valeur est attribuée.
	Algorithme computer : regarde les valeurs possibles pour une cellule donnée. S'il y a une seule valeur possible, la valeur est attribuée.
	Algorithme backtrack : émet une hypothèse sur la valeur d'une cellule et tente de résoudre la grille ainsi modifiée. En cas d'incohérence
		après les autres itérations de l'algorithme global, l'hypothèse est éliminée. S'il n'y a pas d'incohérence, la valeur est confirmée
		et la grille est alors résolue. 
*/

MasterSolve::MasterSolve(Grille *grille){
	grid = grille;
	solver = Solver(grille);
}

/*
	Lance une itération de l'algorithme de détection "humain"
*/

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

/*
	Lance une itération de l'algorithme de détection "computer"
*/

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

/*
	Lance une itération d'algorithme humain. En cas d'échec, lance une itération d'algo computer. En cas d'échec, lance un backtrack.
	Renvoie true si une cellule est devinée, false sinon
*/

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
		return false;
}

//Lance une suite d'itération de l'algorithme jusqu'à résoudre la grille ou trouver une incohérence
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
