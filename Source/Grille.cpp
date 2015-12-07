#include "Grille.h"

/*
	Une grille est un ensemble de 81 cellules
*/

/*
	Constructeur par défaut : toutes les cellules sont initialisées sans valeurs
*/

Grille::Grille() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cells[i][j].setValue(0);
		}
	}
}

Cellule *Grille::getCell(int i, int j) {
	return &cells[i][j];
}

/*
	Constructeur à partir de données entières : toutes les cellules sont initialisées par les valeurs données
*/

Grille::Grille(int * a[9])
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cells[i][j].setValue(a[i][j]);
			cells[i][j].isFixed = a[i][j] != 0;
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
		Cellule *myArray[9];
		int startI = regionI * 3;
		int startJ = regionJ * 3;
		int count = 0;
		for (int i = startI; i < startI + 3; i++) {
			for (int j = startJ; j < startJ + 3; j++) {
				myArray[count] = &cells[i][j];
				count++;
			}
		}
		return NineUplet(myArray);
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
		Cellule *myArray[9];
		for (int j = 0; j < 9; j++) {
			myArray[j] = &cells[i][j];
		}
		return NineUplet(myArray);
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
		Cellule *myArray[9];
		for (int i = 0; i < 9; i++) {
			myArray[i] = &cells[i][j];
		}
		return NineUplet(myArray);
	}
	else {
		throw std::out_of_range("Cell value must be between 0 and 10");
	}
}

bool Grille::isConsistent() {
	bool result = true;
	for (int i = 0; i < 9; i++) {
		result = result && getLine(i).isConsistent();
		if (!result)
			return result;
	}

	for (int j = 0; j < 9; j++) {
		result = result && getColumn(j).isConsistent();
		if (!result)
			return result;
	}

	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 3; i++) {
			result = result && getRegion(i, j).isConsistent();
		}
		if (!result)
			return result;
	}

	return true;
}

bool Grille::isFull() {
	bool result = true;
	for (int i = 0; i < 9; i++) {
		result = result && getLine(i).isFull();
		if (!result)
			return result;
	}
	return true;
}

/*
	Template grid full
*/

Grille Grille::createTemplate() {
	int l1[9] = { 1,2,3,4,5,6,7,8,9 };
	int l2[9] = { 4,5,6,7,8,9,1,2,3 };
	int l3[9] = { 7,8,9,1,2,3,4,5,6 };
	int l4[9] = { 2,3,4,5,6,7,8,9,1 };
	int l5[9] = { 5,6,7,8,9,1,2,3,4 };
	int l6[9] = { 8,9,1,2,3,4,5,6,7 };
	int l7[9] = { 9,1,2,3,4,5,6,7,8 };
	int l8[9] = { 3,4,5,6,7,8,9,1,2 };
	int l9[9] = { 6,7,8,9,1,2,3,4,5 };
	int *data[9] = { l1,l2,l3,l4,l5,l6,l7,l8,l9 };
	Grille grille(data);
	return grille;
}

/*
Template grid with no 2s
*/

Grille Grille::createTemplateMissing() {
	int l1[9] = { 1,0,0,0,0,0,7,8,9 };
	int l2[9] = { 4,5,6,7,0,0,0,0,3 };
	int l3[9] = { 7,0,0,0,0,3,4,5,6 };
	int l4[9] = { 0,3,4,5,6,0,0,0,0 };
	int l5[9] = { 5,6,7,8,0,0,0,0,4 };
	int l6[9] = { 8,0,0,0,0,4,5,6,7 };
	int l7[9] = { 9,1,0,0,0,0,0,6,7};
	int l8[9] = { 3,4,5,6,7,0,0,0,0 };
	int l9[9] = { 6,7,0,0,0,0,3,4,5 };
	int *data[9] = { l1,l2,l3,l4,l5,l6,l7,l8,l9 };
	Grille grille(data);
	return grille;
}

/*
Template grid with no 2s
*/

Grille Grille::createTemplateMissing2() {
	int l1[9] = { 1,0,3,4,5,6,7,8,9 };
	int l2[9] = { 4,5,6,7,8,9,1,0,3 };
	int l3[9] = { 7,8,9,1,0,3,0,5,6 };
	int l4[9] = { 2,3,4,5,6,7,8,9,1 };
	int l5[9] = { 5,6,7,8,9,1,0,3,4 };
	int l6[9] = { 8,9,1,2,3,4,5,6,7 };
	int l7[9] = { 9,1,2,3,4,5,6,7,8 };
	int l8[9] = { 3,4,5,6,7,8,9,1,0 };
	int l9[9] = { 6,7,8,9,1,2,3,4,5 };
	int *data[9] = { l1,l2,l3,l4,l5,l6,l7,l8,l9 };
	Grille grille(data);
	return grille;
}

/*
	Template grid with inconsistent cells
*/

Grille Grille::createTemplateWrong() {
	int l1[9] = { 1,1,3,4,5,6,7,8,9 };
	int l2[9] = { 4,5,6,7,8,9,1,0,3 };
	int l3[9] = { 7,8,9,1,0,3,4,5,6 };
	int l4[9] = { 0,3,4,5,6,7,8,9,1 };
	int l5[9] = { 5,6,7,8,9,1,0,3,4 };
	int l6[9] = { 8,9,1,0,3,4,5,6,7 };
	int l7[9] = { 9,1,0,3,4,5,6,7,8 };
	int l8[9] = { 3,4,5,6,7,8,9,1,0 };
	int l9[9] = { 6,7,8,9,0,2,3,4,5 };
	int *data[9] = { l1,l2,l3,l4,l5,l6,l7,l8,l9 };
	Grille grille(data);
	return grille;
}

/*
	Donne les coordonnées des cellules incohérentes avec la cellule en paramètre
*/

list<list<int>> Grille::getUnconsistentCells(int i, int j) {
	list<list<int>> result;
	Cellule cell = *getCell(i, j);
	if (cell.getValue() != 0) {
		for (int x = 0; x < 9; x++) {
			for (int y = 0; y < 9; y++) {
				Cellule lookedCell = *getCell(x, y);
				if (x != i || y != j) {
					if (lookedCell.getValue() == cell.getValue()) {
						if (x == i || y == j || areInSameRegion(i, j, x, y)) {
							list<int> c = { x,y };
							result.push_front(c);
						}
					}
				}
			}
		}
	}
	return result;
}

/*
	Dit si deux coordonnées sont dans la même région
*/

bool Grille::areInSameRegion(int i, int j, int x, int y) {
	if (i < 9 && i >= 0 && j < 9 && j >= 0) {
		int regionI = (i - (i % 3)) / 3;
		int regionJ = (j - (j % 3)) / 3;
		int regionX = (x - (x % 3)) / 3;
		int regionY = (y - (y % 3)) / 3;
		return regionI == regionX && regionJ == regionY;
	}
}

bool Grille::isCellConsistent(int i, int j) {
	list<list<int>> v = getUnconsistentCells(i, j);
	return (int)v.size() == 0;
}