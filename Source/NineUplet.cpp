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

Cellule **NineUplet::getCells() {
	return cells;
}

Cellule *NineUplet::getCell(int i) {
	return cells[i];
}

bool NineUplet::isPresent(int n)
{
	for (int i = 0; i < 9; i++) {
		if ((*(cells[i])).getValue() == n) {
			return true;
		}
	}
	return false;
}

bool NineUplet::isFull() {
	bool result = true;
	for (int i = 0; i < 9; i++) {
		result = result && (*cells[i]).getValue() != 0;
		if (!result)
			return result;
	}
	return result;
}