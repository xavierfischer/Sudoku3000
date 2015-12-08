#include "stdafx.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{		

	TEST_CLASS(Tests)
	{
	public:
		TEST_METHOD(Master_Solve_Fail)
		{
			Grille grille;
			MasterSolve masterSolve(&grille);
			Assert::IsFalse(masterSolve.solve());
		}

		TEST_METHOD(Master_Solve_Wins_2)
		{
			Grille grille = Grille::createTemplateMissing2();
			MasterSolve masterSolve(&grille);

			Assert::IsTrue(masterSolve.solve());
		}

		TEST_METHOD(Master_Solve_Wins)
		{
			Grille grille = Grille::createTemplateMissing();
			MasterSolve masterSolve(&grille);

			Assert::IsTrue(masterSolve.solve());
		}

		TEST_METHOD(Master_Solve_Grille_eparse)
		{
			Grille grille = Grille::createTemplateEparse();
			MasterSolve masterSolve(&grille);
			bool result = masterSolve.solve();
			Assert::AreEqual(0, grille.emptyValues());
			Assert::IsTrue(result);
		}

		TEST_METHOD(Master_Solve_Grille_difficile)
		{
			Grille grille = Grille::createTemplateDifficile();
			MasterSolve masterSolve(&grille);
			bool result = masterSolve.solve();
			Assert::AreEqual(0, grille.emptyValues());
			Assert::IsTrue(result);
		}

		TEST_METHOD(Master_Solve_Grille_diabolique)
		{
			Grille grille = Grille::createTemplateDiabolique();
			MasterSolve masterSolve(&grille);
			bool result = masterSolve.solve();
			Assert::AreEqual(0, grille.emptyValues());
			Assert::IsTrue(result);
		}
	};
}