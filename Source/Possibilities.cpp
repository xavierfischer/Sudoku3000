#include "Possibilities.h"


Possibilities::Possibilities() {
	for (int i = 0; i < 10; i++) {
		possibilities[i] = true;
	}
}

bool Possibilities::getPossibility(int i) {
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
	for (int i = 0; i < 10; i++) {
		count += possibilities[i] ? 1 : 0;
		value = possibilities[i] ? i : value;
	}
	return count == 1 ? value : 0;
}