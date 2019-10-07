//STD Headers

//Library Headers
#include "CppUnitTest.h"

//Void Engine Headers
#include "Configurable.h"
#include "ThreadPool.h"
#include "ResourceAllocator.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace utils;

namespace EngineUtilitiesTests {

	class DummyConfigurable : public Configurable {
	public:
		DummyConfigurable(ResourceHandle<Configuration> handle) 
			: Configurable(handle) {
			StringProperty = "Error";
			IntegerProperty = -1;
			FloatProperty = -1.0f;
		}

		void Configure() override {
			auto config = Config.GetResource();
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
			auto resourceMngr = std::make_shared<ResourceAllocator<Configuration>>(pool);

			DummyConfigurable d(
				resourceMngr->LoadResource("Settings/Testing/ConfigurableTest1.json")
			);

			d.Configure();

			Assert::AreEqual(std::string("testString1"), d.StringProperty);
			Assert::AreEqual(1, d.IntegerProperty);
			Assert::AreEqual(1.0f, d.FloatProperty);
		}

		TEST_METHOD(ConfigurableReconfigureTest) {
			std::shared_ptr<ThreadPool> pool = std::make_shared<ThreadPool>();
			auto resourceMngr = std::make_shared<ResourceAllocator<Configuration>>(pool);
			auto resource1 = resourceMngr->LoadResource("Settings/Testing/ConfigurableTest1.json");
			auto resource2 = resourceMngr->LoadResource("Settings/Testing/ConfigurableTest2.json");
			
			DummyConfigurable d(
				resource1
			);

			d.Configure();

			Assert::AreEqual(std::string("testString1"), d.StringProperty);
			Assert::AreEqual(1, d.IntegerProperty);
			Assert::AreEqual(1.0f, d.FloatProperty);

			d.Reconfigure(
				resource2
			);

			Assert::AreEqual(std::string("test2"), d.StringProperty);
			Assert::AreEqual(2, d.IntegerProperty);
			Assert::AreEqual(2.0f, d.FloatProperty);
		}
	};

}