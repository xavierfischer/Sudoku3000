#ifndef __Sudoku__POSSIBILITIES__
#define __Sudoku__POSSIBILITIES__

#include "Header.h"

class Possibilities {

public:
	Possibilities();
	bool getPossibility(int);
	void setPossibility(int, bool);
	int possibles();
	int resolve();
	void setAllTo(bool);
	void attach(int, int);
	int attachedI;
	int attachedJ;

private:
	bool possibilities[9];
};

#endif
