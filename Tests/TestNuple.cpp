#include "stdafx.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	Cellule aV[9] = { Cellule(1), Cellule(2), Cellule(3), Cellule(4), Cellule(5), Cellule(6), Cellule(7), Cellule(8), Cellule(9) };
	Cellule bV[9] = { Cellule(), Cellule(2), Cellule(3), Cellule(4), Cellule(5), Cellule(6), Cellule(7), Cellule(8), Cellule(9) };
	Cellule cV[9] = { Cellule(1), Cellule(1), Cellule(3), Cellule(4), Cellule(5), Cellule(6), Cellule(7), Cellule(8), Cellule(9) };
	Cellule dV[9] = { Cellule(), Cellule(), Cellule(), Cellule(), Cellule(), Cellule(), Cellule(), Cellule(), Cellule()};

	Cellule *a[9] = { &aV[0], &aV[1], &aV[2], &aV[3], &aV[4], &aV[5], &aV[6], &aV[7], &aV[8] };
	Cellule *b[9] = { &bV[0], &bV[1], &bV[2], &bV[3], &bV[4], &bV[5], &bV[6], &bV[7], &bV[8] };
	Cellule *c[9] = { &cV[0], &cV[1], &cV[2], &cV[3], &cV[4], &cV[5], &cV[6], &cV[7], &cV[8] };
	Cellule *d[9] = { &dV[0], &dV[1], &dV[2], &dV[3], &dV[4], &dV[5], &dV[6], &dV[7], &dV[8] };

	NineUplet regionA(a);
	NineUplet regionB(b);
	NineUplet regionC(c);
	NineUplet regionD(d);

	TEST_CLASS(Tests)
	{
	public:
		TEST_METHOD(Création_de_Nuple)
		{

			for (int i = 0; i < 9; i++) {
				Assert::AreEqual(0,(*regionD.getCell(i)).getValue());
				int j = (*regionA.getCell(i)).getValue();
				Assert::AreEqual(j, i + 1);
			}
		}

		TEST_METHOD(Is_Nuple_Consistent)
		{
			Assert::IsTrue(regionA.isConsistent());
			Assert::IsTrue(regionB.isConsistent());
			Assert::IsFalse(regionC.isConsistent());
			Assert::IsTrue(regionD.isConsistent());
		}

		TEST_METHOD(Is_Nuple_Full)
		{
			Assert::IsTrue(regionA.isFull());
			Assert::IsFalse(regionD.isFull());
			Assert::IsFalse(regionB.isFull());
			Assert::IsTrue(regionC.isFull());
		}
	};
}