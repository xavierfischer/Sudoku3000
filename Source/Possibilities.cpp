#include "Possibilities.h"


Possibilities::Possibilities() {
	setAllTo(true);
	attachedI = -1;
	attachedJ = -1;
}

bool Possibilities::getPossibility(int i) { // not real value
	return possibilities[i];
}

void Possibilities::setPossibility(int i, bool value) {
	possibilities[i] = value;
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
	int value = 0;
	for (int i = 0; i < 9; i++) {
		count += possibilities[i] ? 1 : 0;
		value = possibilities[i] ? i : value;
	}
	return count == 1 ? (value+1) : 0;
}

void Possibilities::setAllTo(bool v) {
	for (int i = 0; i < 9; i++) {
		possibilities[i] = v;
	}
}

void Possibilities::attach(int i, int j) {
	attachedI = i;
	attachedJ = j;
}