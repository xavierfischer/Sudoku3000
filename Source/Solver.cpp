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

/*
	Réinitialise les tableaux de possibilités pour toutes les cellules
*/

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
		int a = -2;
		for (int j = 0; j < 9; j++) { // pour chaque cellule de la région
			if (a != -1) { // Deux possibilités déjà trouvées
				if (((*(*nuple.getCell(j)).getPossibilities())).getPossibility(value - 1)) {
					a = a == -2 ? j : -1;
				}
			}
		}
		if (a != -1 && a != -2) { // Si on a bien une et une seule valeur
			localCoord = a;
		}
	}
	return localCoord;
}

/*
	Retourne un triplet de integer représentant un guess sur une prochaine valeur
	La méthode de guess est celle consistant à lister tes les places possibles pour une valeur dans une région, une ligne
	ou une colonne

	[0] : ligne du guess
	[1] : colonne du guess
	[2] : valeur du guess
*/

int *Solver::hintHuman() {
	int coords[3] = { 0,0,0 };

	for (int i = 1; i < 10; i++) { // pour chaque valeur
		coords[2] = i;

		for (int x = 0; x < 9; x++) { // pour chaque ligne
			NineUplet line = (*grid).getLine(x);
			int localCoord = hintHumanInNuple(line, i);
			if (localCoord != -1) {
				coords[0] = x;
				coords[1] = localCoord;
				hintableHuman = true;
				return coords;
			}
		}

		for (int x = 0; x < 9; x++) { // pour chaque ligne
			NineUplet column = (*grid).getColumn(x);
			int localCoord = hintHumanInNuple(column, i);
			if (localCoord != -1) {
				coords[0] = localCoord;
				coords[1] = x;
				hintableHuman = true;
				return coords;
			}
		}

		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 3; y++) {
				NineUplet region = (*grid).getRegionA(y,x);
				int localCoord = hintHumanInNuple(region, i);
				if (localCoord != -1) {
					//Formules foireuses
					coords[1] = x * 3 + (localCoord % 3);
					coords[0] = y * 3 + (localCoord - localCoord % 3) / 3;
					hintableHuman = true;
					return coords;
				}
			}
		}
	}
	hintableHuman = false;
	coords[2] = 0;
	return coords;
}

/*
	Retourne un triplet de integer représentant un guess sur une prochaine valeur
	La méthode de guess est celle consistant à lister toutes les possibilités d'une cellule et à attribuer une valeur s'il
	y a une unique possibilité

	[0] : ligne du guess
	[1] : colonne du guess
	[2] : valeur du guess
*/

int *Solver::hintComputer() {
	int coords[3] = { 0, 0, 0 };
	if (leftPossibilities.size() > 0) {

		Possibilities p = leftPossibilities.front();
		int i = p.attachedI;
		int j = p.attachedJ;
		bool isAttributed = true;

		while (isAttributed) {
			if (leftPossibilities.size() == 0) {
				return coords;
			}
			else {
				p = leftPossibilities.front();
				i = p.attachedI;
				j = p.attachedJ;
				if (!(*(*grid).getCell(i, j)).isEmpty()) {
					isAttributed = true;
					leftPossibilities.pop_front();
				}
				else {
					isAttributed = false;
				}
			}
		}

		Possibilities realP = getPossibilities(i, j);
		int value = realP.resolve(); // realValue
		if (value != 0) {
			//Cellule *cell = (*grid).getCell(i,j);
			//(*cell).setValue(value); // realValue
			leftPossibilities.pop_front();
			hintableComputer = true;
			coords[0] = i;
			coords[1] = j;
			coords[2] = value; // realValue
		}
		else {
			if (realP.possibles() == 2) {

				//Backtrack : 

				int value1 = 0;
				int value2 = 0;
				for (int i = 0; i < 9; i++) {
					value1 = (value1 == 0 && realP.getPossibility(i)) ? (i + 1) : value1;
					value2 = (value1 != 0 && realP.getPossibility(i)) ? (i + 1) : value2;
				}

			}
			else {
				hintableComputer = false;
			}
		}
	}
	else {
		hintableComputer = false;
	}
	return coords;
}



/*
	Renvoie les neuf possibilités de la case (i,j), sous forme d'un array de booléens
*/

Possibilities Solver::getPossibilities(int i, int j)
{
	return *(*(*grid).getCell(i,j)).getPossibilities();
}

bool Solver::isHintableComputer() {
	return hintableComputer;
}

bool Solver::isHintableHuman() {
	return hintableHuman;
}