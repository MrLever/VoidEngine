//STD Headers

//Library Headers
#include "gtest/gtest.h"

//Void Engine Headers
#include "utils/configuration/Configurable.h"
#include "utils/threading/ThreadPool.h"
#include "utils/resource/ResourceAllocator.h"
#include "EngineCore/Game.h"

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


	TEST(ConfigurableTests, ConfigurableConfigureTest) {
		core::Game g("");
		auto resourceMngr = std::make_shared<ResourceAllocator<Configuration>>();

		DummyConfigurable d(
			resourceMngr->LoadResource("Settings/Testing/ConfigurableTest1.json")
		);

		d.Configure();

		ASSERT_EQ(std::string("testString1"), d.StringProperty);
		ASSERT_EQ(1, d.IntegerProperty);
		ASSERT_EQ(1.0f, d.FloatProperty);
	}

	TEST(ConfigurableTests, ConfigurableReconfigureTest) {
		core::Game g("");
		auto resourceMngr = std::make_shared<ResourceAllocator<Configuration>>();
		auto resource1 = resourceMngr->LoadResource("Settings/Testing/ConfigurableTest1.json");
		auto resource2 = resourceMngr->LoadResource("Settings/Testing/ConfigurableTest2.json");
			
		DummyConfigurable d(
			resource1
		);

		d.Configure();

		ASSERT_EQ(std::string("testString1"), d.StringProperty);
		ASSERT_EQ(1, d.IntegerProperty);
		ASSERT_EQ(1.0f, d.FloatProperty);

		d.Reconfigure(
			resource2
		);

		ASSERT_EQ(std::string("test2"), d.StringProperty);
		ASSERT_EQ(2, d.IntegerProperty);
		ASSERT_EQ(2.0f, d.FloatProperty);
	}

}