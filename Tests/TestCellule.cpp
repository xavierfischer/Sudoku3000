#include "stdafx.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{		
	TEST_CLASS(Tests)
	{
	public:
		TEST_METHOD(Création_de_cellule)
		{
			Cellule cellA;
			Assert::AreEqual(cellA.getValue(), 0);
			Cellule cellB(5);
			Assert::AreEqual(cellB.getValue(), 5);
		}

		TEST_METHOD(Is_fixed) {
			Cellule cGuessed;
			Cellule cFixed(3);
			Assert::IsTrue(cFixed.isFixed);
			Assert::IsFalse(cGuessed.isFixed);
		}

		TEST_METHOD(Grille_Is_Fixed) {
			Grille grille;
			Assert::IsFalse((*grille.getCell(3, 5)).isFixed);
			Grille grilleFull = Grille::createTemplate();
			Assert::IsTrue((*grilleFull.getCell(3, 5)).isFixed);
		}
	};
}