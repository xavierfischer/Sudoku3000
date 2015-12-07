#include "stdafx.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Tests)
	{
	public:
		TEST_METHOD(Création_de_grille_vide)
		{
			Grille grille;
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					Assert::AreEqual((*grille.getCell(i, j)).getValue(), 0);
				}
			}

			Assert::IsFalse(grille.isFull());
			Assert::IsTrue(grille.isConsistent());

		}

		TEST_METHOD(Création_de_grille_pleine)
		{
			Grille grille;
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					(*grille.getCell(i, j)).setValue(5);
				}
			}

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					Assert::AreEqual((*grille.getCell(i, j)).getValue(), 5);
				}
			}

			Assert::IsFalse(grille.isConsistent());
			Assert::IsTrue(grille.isFull());
		}

		TEST_METHOD(Grille_Complete) {
			Grille grille = Grille::createTemplate();
			Assert::IsTrue(grille.isFull());
			Assert::IsTrue(grille.isConsistent());
			Grille grille2 = Grille::createTemplateMissing();
			Assert::IsFalse(grille2.isFull());
		}

		TEST_METHOD(Unconsistent_Finding_In_Consistent_Grid) {
			Grille grille = Grille::createTemplate();
			
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					list<list<int>> unconstistentCells = grille.getUnconsistentCells(i, j);
					Assert::AreEqual((int) unconstistentCells.size(), 0);
				}
			}
		}

		TEST_METHOD(Unconsistent_Finding_In_Unconsistent_Grid) {

			Grille grille = Grille::createTemplateWrong();
			list<list<int>> unconstistentCells = grille.getUnconsistentCells(0,0);
			Assert::AreEqual((int)unconstistentCells.size(), 1);
			list<int> unconsistentCoord = unconstistentCells.front();

			//La coordonnée incohérente doit être (0,1)
			Assert::AreEqual(unconsistentCoord.front(), 0);
			Assert::AreEqual(unconsistentCoord.back(), 1);

			unconstistentCells = grille.getUnconsistentCells(0, 1);
			Assert::AreEqual((int)unconstistentCells.size(), 2);
			unconsistentCoord = unconstistentCells.front();
		}

	};
}