//STD Headers

//Library Headers
#include "CppUnitTest.h"

//Void Engine Headers
#include "Configurable.h"




using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace EngineUtils;

namespace EngineUtilitiesTests {

	class DummyConfigurable : public Configurable {
	public:
		DummyConfigurable(std::string configFile, std::shared_ptr<ResourceManager> resourceManager) 
			: Configurable(configFile, resourceManager) {
			StringProperty = "Error";
			IntegerProperty = -1;
			FloatProperty = -1.0f;
			LoadConfiguration();
		}

		void Configure() override {
			Config = ResourceMngr->GetResource<Configuration>(ConfigFilePath);
			StringProperty = Config->GetAttribute<std::string>("stringProperty");
			IntegerProperty = Config->GetAttribute<int>("integerProperty");
			FloatProperty = Config->GetAttribute<float>("floatProperty");
		}

		std::string StringProperty;
		int IntegerProperty;
		float FloatProperty;
	};

	TEST_CLASS(ConfigurableTests) {
		TEST_METHOD(ConfigurableConfigureTest) {
			std::shared_ptr<ThreadPool> pool = std::make_shared<ThreadPool>();
			ResourceManager resourceMngr(pool);

			DummyConfigurable d(
				"Settings/Testing/ConfigurableTest1.lua", 
				std::make_shared<ResourceManager>(resourceMngr)
			);

			d.Configure();

			Assert::AreEqual(std::string("testString1"), d.StringProperty);
			Assert::AreEqual(1, d.IntegerProperty);
			Assert::AreEqual(1.0f, d.FloatProperty);
		}

		TEST_METHOD(ConfigurableReconfigureTest) {
			std::shared_ptr<ThreadPool> pool = std::make_shared<ThreadPool>();
			ResourceManager resourceMngr(pool);

			DummyConfigurable d(
				"Settings/Testing/ConfigurableTest1.lua",
				std::make_shared<ResourceManager>(resourceMngr)
			);

			d.Configure();

			Assert::AreEqual(std::string("testString1"), d.StringProperty);
			Assert::AreEqual(1, d.IntegerProperty);
			Assert::AreEqual(1.0f, d.FloatProperty);

			d.Reconfigure("Settings/Testing/ConfigurableTest2.lua");
			Assert::AreEqual(std::string("test2"), d.StringProperty);
			Assert::AreEqual(2, d.IntegerProperty);
			Assert::AreEqual(2.0f, d.FloatProperty);
		}
	};

}