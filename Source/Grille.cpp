#include "Grille.h"
#include <time.h>
#include <stdlib.h>
/*
	Cette classe d�finit une grille de 81 cellules. 
*/

//Constructeur par d�faut : toutes les cellules sont initialis�es sans valeurs, la grille est donc vide
Grille::Grille() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cells[i][j].setValue(0);
		}
	}
}

//Constructeur � partir de donn�es enti�res : toutes les cellules sont initialis�es par les valeurs donn�es
Grille::Grille(int * a[9])
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cells[i][j].setValue(a[i][j]);
			cells[i][j].isFixed = a[i][j] != 0;
		}
	}
}

Cellule *Grille::getCell(int i, int j) {
	return &cells[i][j];
}

/*
	Retourne un NineUplet (ensemble de neuf pointeurs de cellules) repr�sentant la r�gion o� se trouve la cellule (i, j)
*/

NineUplet Grille::getRegionFromCell(int i, int j)
{
	if (i < 9 && i >= 0 && j < 9 && j >= 0) {
		int regionI = (i - (i % 3)) / 3;
		int regionJ = (j - (j % 3)) / 3;
		return getRegionA(regionI, regionJ);
	}
	else {
		throw std::out_of_range("Cell value must be between 0 and 9");
	}
}

/*
	Retourne une NineUplet repr�sentant la r�gion de coordonn�es (i,j) (i, j = 0, 1 ou 2)
*/

NineUplet Grille::getRegionA(int regionI, int regionJ)
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

//Indique si une grille ne pr�sente pas d'irr�gularit�s
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
			result = result && getRegionA(i, j).isConsistent();
		}
		if (!result)
			return result;
	}
	return true;
}

// Indique si une grille est remplie
bool Grille::isFull() {
	bool result = true;
	for (int i = 0; i < 9; i++) {
		result = result && getLine(i).isFull();
		if (!result)
			return result;
	}
	return true;
}

// Renvoie le nombre de cellules vides dans une grille
int Grille::emptyValues() {
	int count = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			count += cells[i][j].isEmpty() ? 1 : 0;
		}
	}
	return count;
}


/*
	Retourne la liste des coordonn�es des cellules incoh�rentes avec la cellule pass�e param�tre
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

// Indique si deux coordonn�es sont dans une m�me r�gion
bool Grille::areInSameRegion(int i, int j, int x, int y) {
	if (i < 9 && i >= 0 && j < 9 && j >= 0) {
		int regionI = (i - (i % 3)) / 3;
		int regionJ = (j - (j % 3)) / 3;
		int regionX = (x - (x % 3)) / 3;
		int regionY = (y - (y % 3)) / 3;
		return regionI == regionX && regionJ == regionY;
	}
}

//Indique si la cellule de coordonn�es (i,j) pr�sent des irr�gularit�s ou non
bool Grille::isCellConsistent(int i, int j) {
	list<list<int>> v = getUnconsistentCells(i, j);
	return (int)v.size() == 0;
}

/*
	TEMPLATES : 
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

Grille Grille::createTemplateMissing() {
	int l1[9] = { 1,0,3,4,5,6,7,8,9 };
	int l2[9] = { 4,5,6,7,8,9,1,0,3 };
	int l3[9] = { 7,8,9,1,0,3,4,5,6 };
	int l4[9] = { 0,3,4,5,6,7,8,9,1 };
	int l5[9] = { 5,6,7,8,9,1,0,3,4 };
	int l6[9] = { 8,9,1,0,3,4,5,6,7 };
	int l7[9] = { 9,1,0,3,4,5,6,7,8 };
	int l8[9] = { 3,4,5,6,7,8,9,1,0 };
	int l9[9] = { 6,7,8,9,1,0,3,4,5 };
	int *data[9] = { l1,l2,l3,l4,l5,l6,l7,l8,l9 };
	Grille grille(data);
	return grille;
}

Grille Grille::createTemplateEparse() {
	int l1[9] = { 1,0,0,0,0,0,7,8,9 };
	int l2[9] = { 4,5,6,7,0,0,0,0,3 };
	int l3[9] = { 7,0,0,0,0,3,4,5,6 };
	int l4[9] = { 0,3,0,0,0,0,8,9,1 };
	int l5[9] = { 5,6,0,0,0,0,0,3,4 };
	int l6[9] = { 0,0,0,0,3,4,5,6,7 };
	int l7[9] = { 9,1,0,0,0,0,0,7,8 };
	int l8[9] = { 3,4,5,0,0,0,0,1,0 };
	int l9[9] = { 0,0,0,0,1,0,3,4,5 };
	int *data[9] = { l1,l2,l3,l4,l5,l6,l7,l8,l9 };
	Grille grille(data);
	return grille;
}

Grille Grille::createTemplateDifficile() {
	int l1[9] = { 7,0,2,8,9,0,0,0,0 };
	int l2[9] = { 0,4,0,0,0,0,0,0,2 };
	int l3[9] = { 6,0,5,0,0,0,0,0,0 };
	int l4[9] = { 8,0,0,2,0,4,0,0,0 };
	int l5[9] = { 2,0,7,6,0,9,1,0,4 };
	int l6[9] = { 0,0,0,5,0,7,0,0,6 };
	int l7[9] = { 0,0,0,0,0,0,8,0,1 };
	int l8[9] = { 1,0,0,0,0,0,0,6,0 };
	int l9[9] = { 0,0,0,0,5,6,2,0,7 };
	int *data[9] = { l1,l2,l3,l4,l5,l6,l7,l8,l9 };
	Grille grille(data);
	return grille;
}

Grille Grille::createTemplateDiabolique() {
	int l1[9] = { 6,5,0,0,0,0,0,9,7};
	int l2[9] = { 0,0,0,0,6,0,8,0,0 };
	int l3[9] = { 3,0,0,4,0,9,0,0,0 };
	int l4[9] = { 0,0,0,0,7,0,2,0,3 };
	int l5[9] = { 0,2,0,0,8,0,0,4,0 };
	int l6[9] = { 7,0,3,0,4,0,0,0,0 };
	int l7[9] = { 0,0,0,1,0,4,0,0,5 };
	int l8[9] = { 0,0,5,0,9,0,0,0,0 };
	int l9[9] = { 1,8,0,0,0,0,0,6,2 };
	int *data[9] = { l1,l2,l3,l4,l5,l6,l7,l8,l9 };
	Grille grille(data);
	return grille;
}

Grille Grille::createTemplateHumanTest() {
	int l1[9] = { 0,0,0,0,0,0,0,0,0 };
	int l2[9] = { 0,0,0,0,1,0,0,0,0 };
	int l3[9] = { 0,0,0,0,0,0,0,1,0 };
	int l4[9] = { 0,0,0,0,0,0,0,0,0 };
	int l5[9] = { 0,0,0,0,0,0,0,0,0 };
	int l6[9] = { 0,1,0,0,0,0,0,0,0 };
	int l7[9] = { 0,0,0,0,0,0,0,0,0 };
	int l8[9] = { 0,0,0,0,0,0,0,0,0 };
	int l9[9] = { 0,0,1,0,0,0,0,0,0 };
	int *data[9] = { l1,l2,l3,l4,l5,l6,l7,l8,l9 };
	Grille grille(data);
	return grille;
}

Grille Grille::createTemplateMissing2() {
	int l1[9] = { 1,0,3,4,5,6,7,8,9 };
	int l2[9] = { 4,5,6,7,8,9,1,0,3 };
	int l3[9] = { 7,8,9,1,0,3,0,5,6 };
	int l4[9] = { 0,3,4,5,6,7,8,9,1 };
	int l5[9] = { 5,6,7,8,9,1,0,3,4 };
	int l6[9] = { 8,9,1,0,3,4,5,6,7 };
	int l7[9] = { 9,1,0,3,4,5,6,7,8 };
	int l8[9] = { 3,4,5,6,7,8,9,1,0 };
	int l9[9] = { 6,7,8,9,1,0,3,4,5 };
	int *data[9] = { l1,l2,l3,l4,l5,l6,l7,l8,l9 };
	Grille grille(data);
	return grille;
}

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

Grille Grille::createTemplateEmpty() {
	int l1[9] = { 0,0,0,0,0,0,0,0,0 };
	int l2[9] = { 0,0,0,0,0,0,0,0,0 };
	int l3[9] = { 0,0,0,0,0,0,0,0,0 };
	int l4[9] = { 0,0,0,0,0,0,0,0,0 };
	int l5[9] = { 0,0,0,0,0,0,0,0,0 };
	int l6[9] = { 0,0,0,0,0,0,0,0,0 };
	int l7[9] = { 0,0,0,0,0,0,0,0,0 };
	int l8[9] = { 0,0,0,0,0,0,0,0,0 };
	int l9[9] = { 0,0,0,0,0,0,0,0,0 };
	int *data[9] = { l1,l2,l3,l4,l5,l6,l7,l8,l9 };
	Grille grille(data);
	return grille;
}




Grille Grille::rdmGrille()
{	
	std::srand(time(NULL));
	int n = std::rand() % 10 + 1;
	switch (n){//On cr�e une Grille al�atoirement entre les 10 qu'on a hardcod�es
	case 1:
		return createTemplate1();
	case 2:
		return createTemplate2();
	case 3:
		return createTemplate3();
	case 4:
		return createTemplate4();
	case 5:
		return createTemplate5();
	case 6:
		return createTemplate6();
	case 7:
		return createTemplate7();
	case 8:
		return createTemplate8();
	case 9:
		return createTemplate9();
	case 10:
		return createTemplate10();
	default:
		return createTemplateEmpty();

	}
}

Grille Grille::createTemplate1() {
	int l1[9] = { 0,5,1,0,7,2,0,6,0 };
	int l2[9] = { 6,0,0,3,0,0,2,0,0 };
	int l3[9] = { 2,3,0,0,1,4,0,5,0 };
	int l4[9] = { 0,0,0,0,9,7,1,0,4 };
	int l5[9] = { 0,0,0,0,0,0,0,0,0 };
	int l6[9] = { 9,0,2,1,4,0,0,0,0 };
	int l7[9] = { 0,2,0,4,3,0,0,9,7 };
	int l8[9] = { 0,0,8,0,0,6,0,0,5 };
	int l9[9] = { 0,4,0,9,8,0,6,2,0 };
	int *data[9] = { l1,l2,l3,l4,l5,l6,l7,l8,l9 };
	Grille grille(data);
	return grille;
}

Grille Grille::createTemplate2() {
	int l1[9] = { 2,5,0,0,1,8,7,0,0 };
	int l2[9] = { 0,4,0,0,0,9,1,0,0 };
	int l3[9] = { 0,0,0,0,7,5,0,8,0 };
	int l4[9] = { 8,0,3,0,4,0,0,5,0 };
	int l5[9] = { 0,6,4,7,0,2,8,1,0 };
	int l6[9] = { 0,7,0,0,5,0,4,0,2 };
	int l7[9] = { 0,3,0,5,8,0,0,0,0 };
	int l8[9] = { 0,0,5,6,0,0,0,9,0 };
	int l9[9] = { 0,0,7,9,3,0,0,2,4 };
	int *data[9] = { l1,l2,l3,l4,l5,l6,l7,l8,l9 };
	Grille grille(data);
	return grille;
}

Grille Grille::createTemplate3() {
	int l1[9] = { 0,0,0,5,2,8,7,0,6 };
	int l2[9] = { 0,0,4,0,0,3,8,0,1 };
	int l3[9] = { 5,0,8,0,1,4,0,9,0 };
	int l4[9] = { 0,4,1,0,0,0,0,0,9 };
	int l5[9] = { 0,0,0,0,0,0,0,0,0 };
	int l6[9] = { 3,0,0,0,0,0,1,7,0 };
	int l7[9] = { 0,1,0,2,3,0,4,0,8 };
	int l8[9] = { 8,0,6,7,0,0,9,0,0 };
	int l9[9] = { 4,0,3,8,6,1,0,0,0 };
	int *data[9] = { l1,l2,l3,l4,l5,l6,l7,l8,l9 };
	Grille grille(data);
	return grille;
}

Grille Grille::createTemplate4() {
	int l1[9] = { 0,7,4,6,0,0,0,0,0 };
	int l2[9] = { 0,6,0,2,8,0,4,7,9 };
	int l3[9] = { 0,0,8,0,0,0,5,2,0 };
	int l4[9] = { 9,0,1,8,3,0,0,0,0 };
	int l5[9] = { 0,5,0,9,0,6,0,3,0 };
	int l6[9] = { 0,0,0,0,1,5,9,0,8 };
	int l7[9] = { 0,3,5,0,0,0,2,0,0 };
	int l8[9] = { 6,1,2,0,9,4,0,8,0 };
	int l9[9] = { 0,0,0,0,0,7,3,6,0 };
	int *data[9] = { l1,l2,l3,l4,l5,l6,l7,l8,l9 };
	Grille grille(data);
	return grille;
}

Grille Grille::createTemplate5() {
	int l1[9] = { 4,0,0,6,3,0,0,0,1 };
	int l2[9] = { 0,6,0,8,0,0,0,0,0 };
	int l3[9] = { 9,0,0,0,0,0,6,3,5 };
	int l4[9] = { 5,0,2,3,0,0,0,9,0 };
	int l5[9] = { 8,0,9,1,0,4,5,0,6 };
	int l6[9] = { 0,1,0,0,0,8,4,0,3 };
	int l7[9] = { 6,9,7,0,0,0,0,0,4 };
	int l8[9] = { 0,0,0,0,0,6,0,5,0 };
	int l9[9] = { 3,0,0,0,7,1,0,0,2 };
	int *data[9] = { l1,l2,l3,l4,l5,l6,l7,l8,l9 };
	Grille grille(data);
	return grille;
}

Grille Grille::createTemplate6() {
	int l1[9] = { 4,0,7,0,5,9,0,0,0 };
	int l2[9] = { 0,0,0,0,0,6,9,0,0 };
	int l3[9] = { 0,5,0,8,4,0,6,0,1 };
	int l4[9] = { 1,8,5,0,6,0,0,0,0 };
	int l5[9] = { 0,7,4,9,0,8,3,5,0 };
	int l6[9] = { 0,0,0,0,7,0,1,8,2 };
	int l7[9] = { 9,0,8,0,2,7,0,3,0 };
	int l8[9] = { 0,0,6,5,0,0,0,0,0 };
	int l9[9] = { 0,0,0,3,9,0,7,0,8 };
	int *data[9] = { l1,l2,l3,l4,l5,l6,l7,l8,l9 };
	Grille grille(data);
	return grille;
}

Grille Grille::createTemplate7() {
	int l1[9] = { 0,5,1,0,4,7,8,0,6 };
	int l2[9] = { 0,7,0,2,9,0,3,0,0 };
	int l3[9] = { 6,3,2,0,8,0,0,0,0 };
	int l4[9] = { 0,0,0,0,0,0,5,6,1 };
	int l5[9] = { 0,8,0,0,0,0,0,4,0 };
	int l6[9] = { 5,2,6,0,0,0,0,0,0 };
	int l7[9] = { 0,0,0,0,6,0,9,5,7 };
	int l8[9] = { 0,0,5,0,7,2,0,3,0 };
	int l9[9] = { 7,0,3,5,1,0,6,8,0 };
	int *data[9] = { l1,l2,l3,l4,l5,l6,l7,l8,l9 };
	Grille grille(data);
	return grille;
}

Grille Grille::createTemplate8() {
	int l1[9] = { 9,4,2,0,0,0,3,0,1 };
	int l2[9] = { 7,3,0,0,0,0,0,0,0 };
	int l3[9] = { 1,8,0,7,0,0,0,5,0 };
	int l4[9] = { 0,0,0,4,3,0,1,8,0 };
	int l5[9] = { 0,1,0,2,0,5,0,3,0 };
	int l6[9] = { 0,2,8,0,6,9,0,0,0 };
	int l7[9] = { 0,7,0,0,0,2,0,1,8 };
	int l8[9] = { 0,0,0,0,0,0,0,2,5 };
	int l9[9] = { 2,0,1,0,0,0,6,9,3 };
	int *data[9] = { l1,l2,l3,l4,l5,l6,l7,l8,l9 };
	Grille grille(data);
	return grille;
}

Grille Grille::createTemplate9() {
	int l1[9] = { 4,0,9,0,2,0,0,0,7 };
	int l2[9] = { 7,0,8,9,0,5,0,1,0 };
	int l3[9] = { 0,6,0,4,0,7,9,0,0 };
	int l4[9] = { 0,9,4,0,7,0,0,0,0 };
	int l5[9] = { 0,0,0,1,0,8,0,0,0 };
	int l6[9] = { 0,0,0,0,4,0,1,3,0 };
	int l7[9] = { 0,0,2,7,0,3,0,9,0 };
	int l8[9] = { 0,8,0,2,0,9,6,0,3 };
	int l9[9] = { 9,0,0,0,6,0,2,0,5 };
	int *data[9] = { l1,l2,l3,l4,l5,l6,l7,l8,l9 };
	Grille grille(data);
	return grille;
}

Grille Grille::createTemplate10() {
	int l1[9] = { 3,0,5,0,2,0,0,6,7 };
	int l2[9] = { 8,0,0,6,0,0,3,0,0 };
	int l3[9] = { 0,0,0,0,1,9,0,0,0 };
	int l4[9] = { 0,0,7,0,6,0,0,1,3 };
	int l5[9] = { 1,6,4,0,5,0,9,2,8 };
	int l6[9] = { 2,8,0,0,9,0,5,0,0 };
	int l7[9] = { 0,0,0,1,4,0,0,0,0 };
	int l8[9] = { 0,0,9,0,0,6,0,0,1 };
	int l9[9] = { 6,7,0,0,3,0,8,0,4 };
	int *data[9] = { l1,l2,l3,l4,l5,l6,l7,l8,l9 };
	Grille grille(data);
	return grille;
}