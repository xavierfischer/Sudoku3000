#include "LastCellFinder.h"

/*
	Cette classe permet de trouver la derniere cellule pour chaque region.
*/

LastCellFinder::LastCellFinder(NineUplet n) :nineUplet(n) {}



bool LastCellFinder::fill() {
	nineUplet.getCells();
	if (nineUplet.isConsistent()) {
		for (int i = 0; i < 9; i++) {
	int v = nineUplet.getCells()[i].value;
		}
	}
	return false;


	a = nineUplet.getCells




	
	//On compte le nombre de cellule vide
	for (int i = 0; i <= 8; i++) {
		if (tableCells[i].isEmpty()) {
			pos = i;//On enregistre la position de la derniere cellule vide parcourue (la seule dans le cas qui nous interesse)
		}
	}
	if (count == 1) {//Si on a effectivement un changement à faire (si il n'y a qu'une seule cellule vide)
		for (int i = 1; i <= 9; i++) {//Pour chaque nombre en 1 et 9
			for (int j = 0; j <= 8; j++) {//On compte le nombre de fois qu'il apparait
				if (tableCells[j].numberCell == i) ;
				
			}//Si le nombre n'apparait pas
                               else

			}
		}
		tableCells[pos] = Cell((char)(((int)'0') + num));//On remplace la cellule vide par le nombre num
		triplet1 = TripleHolder(tableCells[0], tableCells[3], tableCells[6]);
		triplet2 = TripleHolder(tableCells[1], tableCells[4], tableCells[7]);
		triplet3 = TripleHolder(tableCells[2], tableCells[5], tableCells[8]);
		return true;
	}
	return false;
	*/
}
