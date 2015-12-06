#include "stdafx.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{		
	TEST_CLASS(Tests)
	{
	public:
		TEST_METHOD(Initialisation_d_un_solver)
		{
			

			Grille grille;
			//Solver solver(grille);

			//solver.initiate();
			Assert::IsTrue(true);
		}
	};
}