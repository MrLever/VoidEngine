#include <memory>
#include <iostream>

#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Source\EngineUtilities.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace ProjectCoatiTestSuite{

	TEST_CLASS(EngineUtilitiesTests) {
	public:
		TEST_METHOD(FNV1aEqualityTest) {
			auto first = EngineUtilities::FNV1aHash("ThisIsATest");
			auto second = EngineUtilities::FNV1aHash("ThisIsATest");

			Assert::AreEqual(first, second);
		}

		TEST_METHOD(FNV1aInequalityTest) {
			auto first = EngineUtilities::FNV1aHash("ThisIsATest");
			auto second = EngineUtilities::FNV1aHash("SoSoThisIsATest");

			Assert::AreNotEqual(first, second);
		}
	};
}