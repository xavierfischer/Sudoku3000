#include "Solver.h"

/*
	Cette classe permet de solver en backtrack une grille
*/

Solver::Solver(Grille g) :grid(g) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			for (int k = 0; k < 9; k++) {
				possibilities[i][j][k] = true;
			}
		}
	}
}

void Solver::calcPoss(NineUplet &region, NineUplet &line, NineUplet &column, bool (*localPossibilities)[9]) {
	for (int k = 0; k < 9; k++) {
		(*localPossibilities)[k] = (!line.isPresent(k+1)) && (!region.isPresent(k+1)) && (!column.isPresent(k+1));
	}
}

void Solver::initiate() {
	for (int i = 0; i < 9; i++) {
		NineUplet line = grid.getLine(i);
		for (int j = 0; j < 9; j++) {
			NineUplet region = grid.getRegionFromCell(i, j);
			NineUplet column = grid.getColumn(j);
			calcPoss(region, line, column, &possibilities[i][j]);
		}
	}
	initiated = true;
}


void Solver::update(int i, int j) {
	NineUplet line = grid.getLine(i);
	NineUplet region = grid.getRegionFromCell(i, j);
	NineUplet column = grid.getColumn(j);
	calcPoss(region, line, column, &possibilities[i][j]);
}

void Solver::humanSolve() {
	//TODO
}

bool *Solver::getPossibilities(int i, int j)
{
	return possibilities[i][j];
}