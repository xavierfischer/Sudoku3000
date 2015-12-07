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

	NineUplet line = (*grid).getLine(i);
	NineUplet region = (*grid).getRegionFromCell(i, j);
	NineUplet column = (*grid).getColumn(j);

	for (int x = 0; x < 9; x++) {
		(*(*line.getCell(x)).getPossibilities()).setPossibility(value - 1, false);
		(*(*region.getCell(x)).getPossibilities()).setPossibility(value - 1, false);
		(*(*column.getCell(x)).getPossibilities()).setPossibility(value - 1, false);
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