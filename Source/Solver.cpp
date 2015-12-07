#include "Solver.h"



/*
	Cette classe permet de solver en backtrack une grille
*/

Solver::Solver(){}

Solver::Solver(Grille *g) :grid(g) {}

/*
	Regarde toutes les cellules et actualise les possibilités
*/

/*
	Comparateur de tableau de possibilités
	Utilisé pour trier les cellules
*/

static bool comparePossibilities(Possibilities &a, Possibilities &b)
{
	int c1 = 0, c2 = 0;
	for (int i = 0; i < 9; i++) {
		c1 += a.getPossibility(i) ? 0 : 1;
		c2 += b.getPossibility(i) ? 0 : 1;
	}
	return c1>c2;
}

void Solver::initiate() {
	leftPossibilities.clear();
	for (int i = 0; i < 9; i++) {
		NineUplet line = (*grid).getLine(i);
		for (int j = 0; j < 9; j++) {
			Possibilities *p = (*(*grid).getCell(i, j)).getPossibilities();
			(*p).attach(i, j);
			NineUplet region = (*grid).getRegionFromCell(i, j);
			NineUplet column = (*grid).getColumn(j);
			if (!(*(*grid).getCell(i, j)).isEmpty()) {
				(*p).setAllTo(false);
			}
			else {
				calcPoss(line, region, column, *p);
				if ((*p).possibles() > 0) {
					leftPossibilities.push_front(*p);
				}
			}
		}
	}
	initiated = true;
	leftPossibilities.sort(comparePossibilities);
}

/*
	Met à jour un tableau de possibilités pour une cellule se trouvant dans une région, une ligne et une colonne données
*/

void Solver::calcPoss(NineUplet const region, NineUplet const line, NineUplet const column, Possibilities &p) {
	for (int k = 0; k < 9; k++) {
		
		p.setPossibility(k,
			   (!line.isPresent(k + 1)) 
			&& (!region.isPresent(k + 1)) 
			&& (!column.isPresent(k + 1))
		);

	}
}

/*
	Retourne -1 si la valeur ne peut pas être décidée ou est déjà présente dans le nuple
	Retour l'indice local de la cellule qui peut être décidée avec cette valeur
*/

int Solver::hintHumanInNuple(NineUplet nuple, int value) {
	int localCoord = -1;
	if (!nuple.isFull() && !nuple.isPresent(value)) {
		int a = 0;
		for (int j = 0; j < 9; j++) { // pour chaque cellule de la région
			if (a != -1) { // Deux possibilités déjà trouvées
				if (((*(*nuple.getCell(j)).getPossibilities())).getPossibility(value - 1)) {
					a = a == 0 ? j : -1;
				}
			}
		}
		if (a != -1 && a != 0) { // Si on a bien une et une seule valeur
			localCoord = a;
		}
	}
	return localCoord;
}

int *Solver::hintHuman() {
	int coords[3] = { 0,0,0 };

	for (int i = 1; i < 10; i++) { // pour chaque valeur
		coords[2] = i;

		for (int x = 0; x < 9; x++) { // pour chaque ligne
			NineUplet line = (*grid).getLine(i);
			int localCoord = hintHumanInNuple(line, i);
			if (localCoord != -1) {
				coords[0] = x;
				coords[1] = localCoord;
				return coords;
			}
		}

		for (int x = 0; x < 9; x++) { // pour chaque ligne
			NineUplet column = (*grid).getColumn(i);
			int localCoord = hintHumanInNuple(column, i);
			if (localCoord != -1) {
				coords[0] = localCoord;
				coords[1] = x;
				return coords;
			}
		}

		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 3; y++) {
				NineUplet region = (*grid).getRegion(x, y);
				int localCoord = hintHumanInNuple(region, i);
				if (localCoord != -1) {
					coords[0] = x * 3 + (localCoord % 3);
					coords[1] = y * 3 + (localCoord - localCoord % 3) / 3;
					return coords;
				}
			}
		}
		return coords;
	}
}

int *Solver::hint() {
	int coords[3] = { 0, 0, 0 };
	if (leftPossibilities.size() > 0) {
		Possibilities p = leftPossibilities.front();
		int i = p.attachedI;
		int j = p.attachedJ;
		Possibilities realP = getPossibilities(i, j);
		int value = realP.resolve(); // realValue
		if (value != 0) {
			Cellule *cell = (*grid).getCell(i,j);
			(*cell).setValue(value); // realValue
			leftPossibilities.pop_front();
			hintable = true;
			coords[0] = i;
			coords[1] = j;
			coords[2] = value; // realValue
		}
		else {
			hintable = false;
		}
	}
	else {
		hintable = false;
	}
	return coords;
}

/*
	TODO
*/


void Solver::update(int i, int j, int value) {
	if (value == 0) { 
		//Si c'est une annulation, alors on réinitialise
		initiate();
	}
	else {
		NineUplet line = (*grid).getLine(i);
		NineUplet region = (*grid).getRegionFromCell(i, j);
		NineUplet column = (*grid).getColumn(j);

		for (int x = 0; x < 9; x++) {
				(*(*line.getCell(x)).getPossibilities()).setPossibility(value - 1, false);
				(*(*region.getCell(x)).getPossibilities()).setPossibility(value - 1, false);
				(*(*column.getCell(x)).getPossibilities()).setPossibility(value - 1, false);
		}
		leftPossibilities.sort(comparePossibilities);
	}
}


/*
	Renvoie les neuf possibilités de la case (i,j), sous forme d'un array de booléens
*/

Possibilities Solver::getPossibilities(int i, int j)
{
	return *(*(*grid).getCell(i,j)).getPossibilities();
}

bool Solver::isHintable() {
	return hintable;
}

bool Solver::isHintableHuman() {
	return hintableHuman;
}