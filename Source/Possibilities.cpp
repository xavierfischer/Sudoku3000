#include "Possibilities.h"

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

int Possibilities::possibles() {
	int count = 0;
	for (int i = 0; i < 9; i++) {
		count += possibilities[i] ? 1 : 0;
	}
	return count;
}

int Possibilities::resolve() {
	int count = 0;
	int index = 0;
	for (int i = 0; i < 9; i++) {
		count += possibilities[i] ? 1 : 0;
		index = possibilities[i] ? i : index;
	}
	return count == 1 ? (index +1) : 0;
}

void Possibilities::setAllTo(bool v) {
	for (int i = 0; i < 9; i++) {
		possibilities[i] = v;
	}
}

void Possibilities::attach(int i, int j) {
	if (i >= 0 && i < 9 && j >= 0 && j < 9) {
		attachedI = i;
		attachedJ = j;
	}
	else {
		int max = i > j ? i : j;
	}
}