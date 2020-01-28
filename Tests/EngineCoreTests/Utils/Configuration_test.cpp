//STD Headers
#include <fstream>

//Library Headers
#include "gtest/gtest.h"


//Void Engine Headers
#include "EngineCore/ResourceAllocator.h"
#include "EngineCore/ThreadPool.h"
#include "EngineCore/Configuration.h"

using namespace utils;

namespace EngineUtilitiesTests {


		TEST(ConfigurationTests, ConfigurationLoadTest) {
			Configuration config("Settings/Testing/ConfigurableTest1.json");
			config.Load();
			auto res = config.GetAttribute<std::string>("stringProperty");
			ASSERT_EQ(std::string("testString1"), res);
		}

		TEST(ConfigurationTests, ConfigurationGetAttributeTest) {
			Configuration config("Settings/Testing/ConfigurableTest2.json");
			config.Load();

			auto res = config.GetAttribute<std::string>("stringProperty");
			ASSERT_EQ(std::string("test2"), res);

			int res2 = config.GetAttribute<int>("integerProperty");
			ASSERT_EQ(2, res2);

			auto res3 = config.GetAttribute<float>("floatProperty");
			ASSERT_EQ(2.0f, res3, std::numeric_limits<float>::epsilon());

			auto res4 = config.GetAttribute<std::string>("propertyThatIsntThere");
			ASSERT_EQ(std::string(), res4);
		}

		TEST(ConfigurationTests, LoadErrorScriptTest) {
			Configuration config("Nonsense");
			config.Load();

			auto res = config.GetAttribute<bool>("Error");

			ASSERT_TRUE(res);
		}

}