#ifndef __Sudoku__LastCellFinder__
#define __Sudoku__LastCellFinder__

#include "Header.h"
#include "NineUplet.h"

class LastCellFinder {

public:
    LastCellFinder(NineUplet);
    bool fill();

private:
	NineUplet nineUplet;
};
#endif /* defined(__Sudoku__LastCellFinder__) */
