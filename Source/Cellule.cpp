#include "Cellule.h"

/*
    On definit ici la classe cellule et on verifie que chaque cellule est bien remplie
    Chaque cellule est definie comme un couple (iValue, NumberCell) où
        iValue represente la valeur textuelle de la cellule, celle qui est affichée dans l'interface
        numberCell représente la valeur numérique de la cellule
*/

// Constructeur par défaut
Cellule::Cellule() {
	value = 0;
	isFixed = false;
}

// Constructeur avec une valeur
Cellule::Cellule(int n){
	value = n;
	isFixed = n!=0;
	for (int i = 0; i < 10; i++) {
		possibilities.setPossibility(i, false);
	}
}

bool Cellule::isEmpty() {
	return value == 0;
}

int Cellule::getValue()
{
	return value;
}

void Cellule::setValue(int n) {
	if (n >= 0 && n <= 9) {
		value = n;
	}
	else {
		throw 0;
	}
}

// Renvoie le tableau des possibilités associé à cette cellule
Possibilities *Cellule::getPossibilities() {
	return &possibilities;
}

