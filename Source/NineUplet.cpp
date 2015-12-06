#include "NineUplet.h"

/**
	NineUplet : ensemble de neuf cellules
*/

NineUplet::NineUplet(Cellule *a[9]){
	for (int i = 0; i < 9; i++) {
		cells[i] = a[i];
	}
}

bool NineUplet::isConsistent() {
	int count = 0;
	for (int i = 0; i < 9; i++) {
		count = 0;
		for (int j = 0; j < 9; j++) {
			count += ((*(cells[j])).value == i) ? 1 : 0;
			if (count > 1)
				return false;
		}
	}
	return true;
}

Cellule **NineUplet::getCells() {
	return cells;
}