//STD Headers
#include <memory>
#include <iostream>

//Library Headers
#include "CppUnitTest.h"

//Void Engine Headers
#include "EngineUtilities.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace EngineUtils;

namespace EngineUtilitiesTests{

	TEST_CLASS(GenericEngineUtilitiesTests) {
	public:
		TEST_METHOD(FNV1aEqualityTest) {
			auto first = FNV1aHash("ThisIsATest");
			auto second = FNV1aHash("ThisIsATest");

			Assert::AreEqual(first, second);
		}

		TEST_METHOD(FNV1aInequalityTest) {
			auto first = FNV1aHash("ThisIsATest");
			auto second = FNV1aHash("SoSoThisIsATest");

			Assert::AreNotEqual(first, second);
		}
	};
}