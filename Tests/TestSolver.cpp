#include "stdafx.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{		

	Grille blankGrid;

	TEST_CLASS(Tests)
	{
	public:
		TEST_METHOD(Initialisation_d_un_solver)
		{

			Solver solver(blankGrid);

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					bool *c = solver.getPossibilities(i, j);
					for (int k = 0; k < 9; k++) {
						Assert::IsTrue(c[k]);
					}
				}
			}
		}
		TEST_METHOD(Calc_Possibilities) {

			Grille grille = Grille::createTemplate();
			bool possibilities[9] = { true, true, true, true, true, true, true, true, true };

			Solver::calcPoss(grille.getRegion(0, 0), grille.getLine(0), grille.getColumn(0), &possibilities);
			for (int i = 0; i < 9; i++) {
				Assert::IsFalse(possibilities[i]);
			}

		}

		TEST_METHOD(Calc_Possibilities_Missing) {

			Grille grille = Grille::createTemplateMissing();
			bool possibilities[9] = { true, true, true, true, true, true, true, true, true };

			Solver::calcPoss(grille.getRegion(0, 0), grille.getLine(0), grille.getColumn(0), &possibilities);
			for (int i = 0; i < 9; i++) {
				Assert::IsFalse(i == 1 ? !possibilities[i] : possibilities[i]);
			}

		}
		TEST_METHOD(Solver_sur_une_grille_résolue)
		{
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
		}
	};
}