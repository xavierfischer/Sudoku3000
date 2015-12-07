#include "stdafx.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{		

	TEST_CLASS(Tests)
	{
	public:
		TEST_METHOD(Master_Solve_Fail)
		{
			Grille blankGrid;
			MasterSolve masterSolve(&blankGrid);
			bool result = masterSolve.solve();
			Assert::IsFalse(result);
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					Assert::AreEqual(0,(*blankGrid.getCell(i,j)).getValue());
				}
			}
		}

		TEST_METHOD(Master_Solve_Wins)
		{
			Grille grille = Grille::createTemplateMissing2();
			MasterSolve masterSolve(&grille);
			bool result = masterSolve.solve();
			Assert::IsTrue(result);
			Assert::IsTrue(grille.isConsistent());
			Assert::IsTrue(grille.isFull());
		}

		TEST_METHOD(Master_Solve_Wins_2)
		{
			Grille grille = Grille::createTemplateMissing();
			MasterSolve masterSolve(&grille);
			bool result = masterSolve.solve();
			Assert::IsTrue(result);
			Assert::IsTrue(grille.isConsistent());
			Assert::IsTrue(grille.isFull());
		}
	};
}