#include "Grille.h"

/*
	Une grille est un ensemble de 81 cellules
*/

/*
	Constructeur par défaut : toutes les cellules sont initialisées sans valeurs
*/

Grille::Grille() {
	Cellule cells[9][9];
}

/*
	Constructeur à partir de données entières : toutes les cellules sont initialisées par les valeurs données
*/

Grille::Grille(int * a[9])
{
	Cellule cells[9][9];
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cells[i][j] = Cellule();
		}
	}
}

/*
	Retourne un NineUplet représentant la région où se trouve la cellule (i, j)
*/

NineUplet Grille::getRegionFromCell(int i, int j)
{
	if (i < 9 && i >= 0 && j < 9 && j >= 0) {
		int regionI = (i - (i % 3)) / 3;
		int regionJ = (j - (j % 3)) / 3;
		return getRegion(regionI, regionJ);
	}
	else {
		throw std::out_of_range("Cell value must be between 0 and 9");
	}
}

/*
	Retourne une NineUplet représentant la région de coordonnées (i,j) (i, j = 0, 1 ou 2)
*/

NineUplet Grille::getRegion(int regionI, int regionJ)
{
	if (regionI < 3 && regionI >= 0 && regionJ < 3 && regionJ >= 0) {
		Cellule *array[9];
		int startI = regionI * 3;
		int startJ = regionJ * 3;
		int count = 0;
		for (int i = startI; i < startI + 3; i++) {
			for (int j = startJ; i < startJ + 3; j++) {
				array[count] = &cells[i][j];
				count++;
			}
		}
		return NineUplet(array);
	}
	else {
		throw std::out_of_range("Cell value must be between 0 and 9");
	}
}

/*
	Retourne une NineUplet représentant la ligne i
*/

NineUplet Grille::getLine(int i) {
	if (i < 9 && i >= 0) {
		Cellule *array[9];
		for (int j = 0; j < 9; j++) {
			array[j] = &cells[i][j];
		}
		return NineUplet(array);
	}
	else {
		throw std::out_of_range("Cell value must be between 0 and 10");
	}
}


/*
	Retourne une NineUplet représentant la colonne i
*/

NineUplet Grille::getColumn(int j) {
	if (j < 9 && j >= 0) {
		Cellule *array[9];
		for (int i = 0; i < 9; i++) {
			array[i] = &cells[i][j];
		}
		return NineUplet(array);
	}
	else {
		throw std::out_of_range("Cell value must be between 0 and 10");
	}
}