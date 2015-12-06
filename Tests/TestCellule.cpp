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
			Assert::AreEqual(cellA.value, 0);
			Cellule cellB(5);
			Assert::AreEqual(cellB.value, 5);
		}
	};
}