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
	};
}