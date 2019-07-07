//STD Headers

//Library Headers
#include "stdafx.h"
#include "CppUnitTest.h"

//SuperVoid Headers
#include "UUID.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace EngineUtils;

namespace EngineTestSuite {

	TEST_CLASS(UUIDTests) {
		public:

		TEST_METHOD(UUIDConstructorTest) {
			UUID id("Test");

			Assert::AreNotEqual((unsigned long long)0, id.ID);
			Assert::AreEqual(std::string("Test"), id.StringID);
		}

		TEST_METHOD(UUIDComparisonTest) {
			UUID idA("Foo");
			UUID idB("Bar");
			UUID idC("Foo");

			Assert::IsTrue(idA != idB);
			Assert::IsTrue(idA == idC);

			// Relational operators are available but untested
		}
	};
};