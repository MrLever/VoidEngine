#include <memory>
#include <fstream>
#include "stdafx.h"
#include "CppUnitTest.h"

#include "TestingUtilities.h"
#include "Configurable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace EngineCore;

namespace ProjectCoatiTestSuite {

	struct DummyConfigurable : Configurable {
		
		std::string StringProperty;
		int IntegerProperty;
		float FloatProperty;

		DummyConfigurable() : Configurable("testing/ConfigurableTest1.lua") {
			StringProperty = "ERROR";
			IntegerProperty = -1;
			FloatProperty = 1.0;

			Configure();
		}

		DummyConfigurable(std::string file) : Configurable(file) {
			StringProperty = "ERROR";
			IntegerProperty = -1;
			FloatProperty = 1.0;
		}

		void Configure() override {
			//StringProperty = GetAttribute<std::string>("stringProperty");
		}

	};

	TEST_CLASS(ConfigurableTest) {
	public:
		TEST_METHOD(ConfigureTest) {
			DummyConfigurable d;

			Assert::Fail();
		}
	};
}