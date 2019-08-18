//STD Headers

//Library Headers
#include "stdafx.h"
#include "CppUnitTest.h"

//Void Engine Headers
#include "UUID.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace EngineUtils;

namespace EngineUtilitiesTests {

	TEST_CLASS(UUIDTests) {
		public:

		TEST_METHOD(UUIDConstructorTest) {
			UUID id("Test");

			Assert::AreEqual(EngineUtils::FNV1aHash("Test"), id.ID);
			Assert::AreEqual(std::string("Test"), id.StringID);
		}

		TEST_METHOD(UUIDComparisonTest) {
			UUID idA("Foo");
			UUID idB("Bar");
			UUID idC("Foo");

			Assert::IsTrue(idA != idB);
			Assert::IsTrue(idA == idC);
			Assert::IsTrue(idA == "Foo");
			Assert::IsTrue("Foo" == idA);

			// Relational operators are available but untested
		}
	};
};