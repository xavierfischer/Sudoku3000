#include "stdafx.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{		

	Grille blankGrid;

	TEST_CLASS(Tests)
	{
	public:
		TEST_METHOD(Possibilities_Blank_Grid)
		{

			Solver solver(&blankGrid);
			solver.initiate();

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					Possibilities possibilities = *(*blankGrid.getCell(i, j)).getPossibilities();
					for (int k = 0; k < 9; k++) {
						Assert::IsTrue(possibilities.getPossibility(k));
					}
				}
			}
			
			Possibilities p = solver.getPossibilities(0, 0);
			Assert::AreEqual(9, p.possibles());
			Assert::AreEqual(0, p.resolve(), 0);

		}

		TEST_METHOD(Possibilities_Full_Consistent_Grid)
		{
			Grille fullGrid = Grille::createTemplate();

			Solver solver(&fullGrid);
			solver.initiate();

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					Possibilities possibilities = solver.getPossibilities(i, j);
					for (int k = 0; k < 9; k++) {
						Assert::IsFalse(possibilities.getPossibility(k));
					}
				}
			}

			Possibilities p = solver.getPossibilities(0, 0);
			Assert::AreEqual(0, p.possibles());
			
		}

		TEST_METHOD(Calc_Possibilities_Missing) {

			Grille grille = Grille::createTemplateMissing();
			Possibilities *poss = (*grille.getCell(0, 0)).getPossibilities();
			Solver::calcPoss(grille.getRegion(0, 0), grille.getLine(0), grille.getColumn(0), *poss);
			
			for (int i = 0; i < 9; i++) {
				if (i != 1) { // value != 2
					Assert::IsFalse((*poss).getPossibility(i));
				}
				else {
					Assert::IsTrue((*poss).getPossibility(i));
				}
			}
		}

		TEST_METHOD(Possibilities_not_Full_Consistent_Grid)
		{
			Grille grid = Grille::createTemplateMissing();

			Solver solver(&grid);
			solver.initiate();

			int countA = 0;
			int countB = 0;

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					Possibilities possibilities = *(*grid.getCell(i,j)).getPossibilities();
					int possibles = possibilities.possibles();
					Assert::IsTrue(possibles == 1 || possibles == 0);
					if (possibles == 1) {
						countA++;
					}
					else {
						countB++;
					}
				}
			}

			Assert::AreEqual(81, countA + countB);
			Assert::AreEqual(9, countA);

		}

		TEST_METHOD(Hint) {

			Grille grille = Grille::createTemplateMissing();
			Solver solver(&grille);

			solver.initiate();
			for (int i = 0; i < 9; i++) {
				solver.hint();
			}
			Cellule c = *grille.getCell(0, 1);
			Assert::AreEqual(2, c.getValue());

		}


		TEST_METHOD(Complete_Missing_grid) {

			Grille grille = Grille::createTemplateMissing2();
			Solver solver(&grille);

			Assert::IsFalse(grille.isFull());
			Assert::IsTrue(grille.isConsistent());

			solver.initiate();

			while (solver.isHintable()) {
				solver.hint();
			}
			
			Assert::IsTrue(grille.isFull());
			Assert::IsTrue(grille.isConsistent());

		}
	};
}