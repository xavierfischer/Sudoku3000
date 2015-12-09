
#ifndef __Sudoku__GRILLE__
#define __Sudoku__GRILLE__

#include <stdio.h>
#include "Header.h"
#include "Cellule.h"
#include "NineUplet.h"

class Grille {
public:
	Grille();
	Grille(int *a[9]);

	NineUplet getRegionFromCell(int, int);
	NineUplet getRegionA(int, int);
	NineUplet getLine(int);
	NineUplet getColumn(int);

	Cellule *getCell(int, int);
	bool isFull();
	bool isConsistent();
	int emptyValues();

	static Grille createTemplate();
	static Grille createTemplateMissing();
	static Grille createTemplateMissing2();
	static Grille createTemplateWrong();
	static Grille createTemplateEmpty();
	static Grille createTemplateEparse();
	static Grille createTemplateHumanTest();
	static Grille createTemplateDifficile();
	static Grille createTemplateDiabolique();

	static Grille rdmGrille();
	static Grille createTemplate1();
	static Grille createTemplate2();
	static Grille createTemplate3();
	static Grille createTemplate4();
	static Grille createTemplate5();
	static Grille createTemplate6();
	static Grille createTemplate7();
	static Grille createTemplate8();
	static Grille createTemplate9();
	static Grille createTemplate10();

	list<list<int>> getUnconsistentCells(int, int);
	bool isCellConsistent(int i, int j);

private: 
	Cellule cells[9][9];
	static bool areInSameRegion(int, int, int, int);


};



#endif /* defined(__Sudoku__Grid__) */
