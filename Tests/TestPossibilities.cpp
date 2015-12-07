#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{		

	TEST_CLASS(Tests)
	{
	public:
		
		TEST_METHOD(Fonction_resolve_get_result)
		{
			Possibilities p;

			for (int i = 0; i < 9; i++) {
				p.setPossibility(i, false);
			}
			p.setPossibility(3, true); // open possibility for value 4

			int value = p.resolve();
			Assert::AreEqual(4, value);
		
		}

		TEST_METHOD(Fonction_resolve_gets_no_result)
		{
			Possibilities p;
			for (int i = 0; i < 9; i++) {
				p.setPossibility(i, false);
			}
			int value = p.resolve();
			Assert::AreEqual(0, value);

		}


	};
}