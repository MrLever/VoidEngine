//STD Headers

//Library Headers
#include "stdafx.h"
#include "CppUnitTest.h"

//Void Engine Headers
#include "Configurable.h"




using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace EngineUtils;

namespace EngineUtilitiesTests {

	class DummyConfigurable : Configurable {
		DummyConfigurable(std::string name, std::string configFile, std::shared_ptr<ResourceManager> resourceManager) 
			: Configurable(name, configFile, resourceManager) {
			LoadConfiguration();
		}

		void Configure() override {
			Config = ResourceMngr->GetResource<Configuration>(ConfigFilePath);
		}
	};

	TEST_CLASS(ConfigurableTests) {
		TEST_METHOD(ConfigurableConstructionTest) {
			Assert::Fail();
		}
	};

}