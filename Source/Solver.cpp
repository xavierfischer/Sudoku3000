#include "Solver.h"

/*
	Cette classe permet de solver en backtrack une grille
*/

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

void Solver::hint() {
	Possibilities p = leftPossibilities.front();
	int value = p.resolve();
	if (value!=0) {
		Cellule *cell = (*grid).getCell(p.attachedI, p.attachedJ);
		(*cell).setValue(value);
		leftPossibilities.pop_front();
	}
}

/*
	TODO
*/


void Solver::update(int i, int j) {
	/*
	NineUplet line = grid.getLine(i);
	NineUplet region = grid.getRegionFromCell(i, j);
	NineUplet column = grid.getColumn(j);
	calcPoss(region, line, column, *grid.getCell(i, j));
	leftCells.sort(comparePossibilities);
	*/
}


/*
	Renvoie les neuf possibilités de la case (i,j), sous forme d'un array de booléens
*/

Possibilities Solver::getPossibilities(int i, int j)
{
	return *(*(*grid).getCell(i,j)).getPossibilities();
}

