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
		}
	};
}