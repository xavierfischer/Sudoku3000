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

			Solver solver(blankGrid);
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

			Solver solver(fullGrid);
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
			Assert::IsTrue(false);

			/*
			
			
			Grille grille = Grille::createTemplateMissing();
			bool possibilities[9] = { true, true, true, true, true, true, true, true, true };

			Solver::calcPoss(grille.getRegion(0, 0), grille.getLine(0), grille.getColumn(0), &possibilities);
			for (int i = 0; i < 9; i++) {
				Assert::IsFalse(i == 1 ? !possibilities[i] : possibilities[i]);
			}
			
			*/

		}
		TEST_METHOD(Solver_sur_une_grille_résolue)
		{
			Assert::IsTrue(false);

			/*

			Grille grille = Grille::createTemplate();
			Solver solver(grille);
			solver.initiate();

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					bool *c = solver.getPossibilities(i, j);
					for (int k = 0; k < 9; k++) {
						Assert::IsFalse(c[k]);
					}
				}
			}

			*/
		}
	};
}