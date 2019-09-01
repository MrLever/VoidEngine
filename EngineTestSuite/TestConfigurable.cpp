//STD Headers

//Library Headers
#include "CppUnitTest.h"

//Void Engine Headers
#include "Configurable.h"
#include "ThreadPool.h"
#include "ResourceManager.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace EngineUtils;

namespace EngineUtilitiesTests {

	class DummyConfigurable : public Configurable {
	public:
		DummyConfigurable(ResourceHandle handle) 
			: Configurable(handle) {
			StringProperty = "Error";
			IntegerProperty = -1;
			FloatProperty = -1.0f;
		}

		void Configure() override {
			auto config = Config.GetResource<Configuration>();
			StringProperty = config->GetAttribute<std::string>("stringProperty");
			IntegerProperty = config->GetAttribute<int>("integerProperty");
			FloatProperty = config->GetAttribute<float>("floatProperty");
		}

		std::string StringProperty;
		int IntegerProperty;
		float FloatProperty;
	};

	TEST_CLASS(ConfigurableTests) {
		TEST_METHOD(ConfigurableConfigureTest) {
			std::shared_ptr<ThreadPool> pool = std::make_shared<ThreadPool>();
			auto resourceMngr = std::make_shared<ResourceManager>(pool);

			DummyConfigurable d(
				resourceMngr->LoadResource<Configuration>("Settings/Testing/ConfigurableTest1.lua")
			);

			d.Configure();

			Assert::AreEqual(std::string("testString1"), d.StringProperty);
			Assert::AreEqual(1, d.IntegerProperty);
			Assert::AreEqual(1.0f, d.FloatProperty);
		}

		TEST_METHOD(ConfigurableReconfigureTest) {
			std::shared_ptr<ThreadPool> pool = std::make_shared<ThreadPool>();
			auto resourceMngr = std::make_shared<ResourceManager>(pool);
			resourceMngr->LoadResource<Configuration>("Settings/Testing/ConfigurableTest1.lua");
			resourceMngr->LoadResource<Configuration>("Settings/Testing/ConfigurableTest2.lua");
			
			DummyConfigurable d(
				resourceMngr->GetResource<Configuration>("Settings/Testing/ConfigurableTest1.lua")
			);

			d.Configure();

			Assert::AreEqual(std::string("testString1"), d.StringProperty);
			Assert::AreEqual(1, d.IntegerProperty);
			Assert::AreEqual(1.0f, d.FloatProperty);

			d.Reconfigure(
				resourceMngr->GetResource<Configuration>("Settings/Testing/ConfigurableTest2.lua")
			);

			Assert::AreEqual(std::string("test2"), d.StringProperty);
			Assert::AreEqual(2, d.IntegerProperty);
			Assert::AreEqual(2.0f, d.FloatProperty);
		}
	};

}