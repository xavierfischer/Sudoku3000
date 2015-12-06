#include "Solver.h"

/*
	Cette classe permet de solver en backtrack une grille
*/

Solver::Solver(Grille g) :grid(g) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < 10; k++) {
				possibilities[i][j][k] = true;
			}
		}
	}
}

void calcPoss(NineUplet &region, NineUplet &line, NineUplet &column, bool localPossibilities[9]) {
	for (int k = 1; k < 10; k++) {
		localPossibilities[k] = (!line.isPresent(k)) && (!region.isPresent(k)) && (!column.isPresent(k));
	}
}

void Solver::initiate() {
	for (int i = 0; i < 9; i++) {
		NineUplet line = grid.getLine(i);
		for (int j = 0; j < 9; j++) {
			NineUplet region = grid.getRegionFromCell(i, j);
			NineUplet column = grid.getColumn(j);
			calcPoss(region, line, column, possibilities[i][j]);
		}
	}
	initiated = true;
}


void Solver::update(int i, int j) {
	NineUplet line = grid.getLine(i);
	NineUplet region = grid.getRegionFromCell(i, j);
	NineUplet column = grid.getColumn(j);
	calcPoss(region, line, column, possibilities[i][j]);
}

void Solver::humanSolve() {
	//TODO
}