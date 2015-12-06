#include "stdafx.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Tests)
	{
	public:
		TEST_METHOD(Cr�ation_de_grille_vide)
		{
			Grille grille;
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					Assert::AreEqual((*grille.getCell(i, j)).value, 0);
				}
			}

			Assert::IsFalse(grille.isFull());
			Assert::IsTrue(grille.isConsistent());

		}

		TEST_METHOD(Cr�ation_de_grille_pleine)
		{
			Grille grill;
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					(*grill.getCell(i, j)).value = 5;
				}
			}

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					Assert::AreEqual((*grill.getCell(i, j)).value, 5);
				}
			}

			Assert::IsFalse(grill.isConsistent());
			Assert::IsTrue(grill.isFull());
		}
	};
}