#include "Grille.h"

/*
	Une grille est un ensemble de 81 cellules
*/

/*
	Constructeur par d�faut : toutes les cellules sont initialis�es sans valeurs
*/

Grille::Grille() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cells[i][j].value = 0;
		}
	}
}

/*
	Constructeur � partir de donn�es enti�res : toutes les cellules sont initialis�es par les valeurs donn�es
*/

Grille::Grille(int * a[9])
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cells[i][j].value=a[i][j];
		}
	}
}

/*
	Retourne un NineUplet repr�sentant la r�gion o� se trouve la cellule (i, j)
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
	Retourne une NineUplet repr�sentant la r�gion de coordonn�es (i,j) (i, j = 0, 1 ou 2)
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
	Retourne une NineUplet repr�sentant la ligne i
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
	Retourne une NineUplet repr�sentant la colonne i
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

Cellule *Grille::getCell(int i, int j) {
	return &cells[i][j];
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