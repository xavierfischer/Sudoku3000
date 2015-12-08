#include "Possibilities.h"

/*
	Possibilities contient principalement un tableau de neuf booléens. 
	Le booléen à l'index i dans le tableau indique si la cellule peut prendre la valeur i+1.
	Un objet possibilities est associé à chaque cellule, et il est mis à jour à chaque modification de la grille. 
*/

Possibilities::Possibilities() {
	setAllTo(true);
	attachedI = -1;
	attachedJ = -1;
}

bool Possibilities::getPossibility(int indexOfValue) { // not real value
		return possibilities[indexOfValue];
}

void Possibilities::setPossibility(int index, bool indexOfValue) {
	if (index > 9 || index < 0) {
		throw 0;
	}
	else {
		possibilities[index] = indexOfValue;
	}
}

// Renvoie le nombre de valeurs possibles
int Possibilities::possibles() {
	int count = 0;
	for (int i = 0; i < 9; i++) {
		count += possibilities[i] ? 1 : 0;
	}
	return count;
}

// Renvoie, si elle existe, l'unique valeur que peut prendre la cellule. Sinon, renvoie 0;
int Possibilities::resolve() {
	int count = 0;
	int index = 0;
	for (int i = 0; i < 9; i++) {
		count += possibilities[i] ? 1 : 0;
		index = possibilities[i] ? i : index;
	}
	return count == 1 ? (index +1) : 0;
}

// Fixe toutes les possibilités à true ou false
void Possibilities::setAllTo(bool v) {
	for (int i = 0; i < 9; i++) {
		possibilities[i] = v;
	}
}

// Attache à l'objet les entiers i et j qui indiquent les coordonnées de la cellule concernée
void Possibilities::attach(int i, int j) {
	if (i >= 0 && i < 9 && j >= 0 && j < 9) {
		attachedI = i;
		attachedJ = j;
	}
	else {
		int max = i > j ? i : j;
	}
}