#include "NineUplet.h"

/**
	NineUplet : ensemble de neuf cellules. Il peut être une région, une ligne ou une colonne
*/

NineUplet::NineUplet(Cellule *a[9]){
	for (int i = 0; i < 9; i++) {
		cells[i] = a[i];
	}
}

// Indique s'il y a ou non des incohérences entre les cellules de l'ensemble
bool  NineUplet::isConsistent() const {
	int count = 0;
	for (int i = 1; i < 10; i++) {
		count = 0;
		for (int j = 0; j < 9; j++) {
			count += ((*(cells[j])).getValue() == i) ? 1 : 0;
			if (count > 1)
				return false;
		}
	}
	return true;
}

Cellule  **NineUplet::getCells(){
	return cells;
}

Cellule  *NineUplet::getCell(int i)  const {
	return cells[i];
}

//Indique si la valeur n (n=1..9) est présente ou non dans la zone
bool  NineUplet::isPresent(int n) const // realValue
{
	for (int i = 0; i < 9; i++) {
		if ((*(cells[i])).getValue() == n) {
			return true;
		}
	}
	return false;
}

bool NineUplet::isFull() const {
	bool result = true;
	for (int i = 0; i < 9; i++) {
		result = result && (*cells[i]).getValue() != 0;
		if (!result)
			return result;
	}
	return result;
}