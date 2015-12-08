#include "MasterSolve.h"

/*
	Cette grille permet de fa�on simple grace � deux m�thodes solve() et hint() de cr�er un object Solver sur une grille
	et de lancer les algorithmes. 

	Trois fa�ons d'avancer sont impl�ment�es : 

	Algorithme humain : regarde les cellules possibles pour une valeur donn�e. S'il y a une seule cellule possible, la valeur est attribu�e.
	Algorithme computer : regarde les valeurs possibles pour une cellule donn�e. S'il y a une seule valeur possible, la valeur est attribu�e.
	Algorithme backtrack : �met une hypoth�se sur la valeur d'une cellule et tente de r�soudre la grille ainsi modifi�e. En cas d'incoh�rence
		apr�s les autres it�rations de l'algorithme global, l'hypoth�se est �limin�e. S'il n'y a pas d'incoh�rence, la valeur est confirm�e
		et la grille est alors r�solue. 
*/

MasterSolve::MasterSolve(Grille *grille){
	grid = grille;
	solver = Solver(grille);
}

/*
	Lance une it�ration de l'algorithme de d�tection "humain"
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
	Lance une it�ration de l'algorithme de d�tection "computer"
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
	Lance une it�ration d'algorithme humain. En cas d'�chec, lance une it�ration d'algo computer. En cas d'�chec, lance un backtrack.
	Renvoie true si une cellule est devin�e, false sinon
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

//Lance une suite d'it�ration de l'algorithme jusqu'� r�soudre la grille ou trouver une incoh�rence
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
