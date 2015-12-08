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
			Solver::calcPoss(grille.getRegionA(0, 0), grille.getLine(0), grille.getColumn(0), *poss);
			
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

		/*TEST_METHOD(Update) {

			Grille grille;

			Solver solver(&grille);
			solver.initiate();

			Cellule *cell00 = grille.getCell(0, 0);
			NineUplet line = grille.getLine(0);
			NineUplet region = grille.getRegionFromCell(0,0);
			NineUplet column = grille.getColumn(0);

			(*cell00).setValue(1);

			Assert::AreEqual(1,(*grille.getCell(0, 0)).getValue());

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					Assert::IsTrue((*(*line.getCell(j)).getPossibilities()).getPossibility(i));
					Assert::IsTrue((*(*region.getCell(j)).getPossibilities()).getPossibility(i));
					Assert::IsTrue((*(*column.getCell(j)).getPossibilities()).getPossibility(i));
				}
			}

			solver.update(0, 0, 1);

			for (int i = 1; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					Assert::IsTrue((*(*line.getCell(j)).getPossibilities()).getPossibility(i));
					Assert::IsTrue((*(*region.getCell(j)).getPossibilities()).getPossibility(i));
					Assert::IsTrue((*(*column.getCell(j)).getPossibilities()).getPossibility(i));
				}
			}

			for (int j = 0; j < 9; j++) {
				Assert::IsFalse((*(*line.getCell(j)).getPossibilities()).getPossibility(0));
				Assert::IsFalse((*(*region.getCell(j)).getPossibilities()).getPossibility(0));
				Assert::IsFalse((*(*column.getCell(j)).getPossibilities()).getPossibility(0));
			}
		}*/

		TEST_METHOD(Hint_Computer) {

			Grille grille = Grille::createTemplateMissing();
			Solver solver(&grille);

			solver.initiate();

			int *result = solver.hintComputer();
			int value = result[2];

			Assert::AreEqual(2, value);
		}

		TEST_METHOD(Hint_Human) {

			Grille grille = Grille::createTemplateHumanTest();
			Solver solver(&grille);

			solver.initiate();

			int *result = solver.hintHuman();
			int coordx = result[0];
			int coordy = result[1];
			int value = result[2];

			Assert::AreEqual(1, value);
			Assert::AreEqual(0, coordx);
			Assert::AreEqual(0, coordy);
		}


		TEST_METHOD(Complete_Missing_grid) {

			Grille grille = Grille::createTemplateMissing2();
			Solver solver(&grille);

			Assert::IsFalse(grille.isFull());
			Assert::IsTrue(grille.isConsistent());

			solver.initiate();

			while (solver.isHintableComputer()) {
				int *result = solver.hintComputer();
				int i = result[0];
				int j = result[1];
				int value = result[2]; // realValue
				if (value != 0) {
					(*grille.getCell(i, j)).setValue(value);
					solver.initiate();
				}
			}
			
			Assert::IsTrue(grille.isFull());
			Assert::IsTrue(grille.isConsistent());

		}
	};
}