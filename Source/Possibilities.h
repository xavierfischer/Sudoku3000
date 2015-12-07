#ifndef __Sudoku__POSSIBILITIES__
#define __Sudoku__POSSIBILITIES__

class Possibilities {

public:
	Possibilities();
	bool getPossibility(int);
	void setPossibility(int, bool);
	int possibles();
	int resolve();
private:
	bool possibilities[9];
};

#endif
