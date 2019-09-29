//STD Headers
#include <fstream>

//Library Headers
#include "CppUnitTest.h"

//Void Engine Headers
#include "ResourceManager.h"
#include "ThreadPool.h"
#include "Configuration.h"




using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace EngineUtils;

namespace EngineUtilitiesTests {

		TEST_CLASS(ConfigurationResourceTests) {
			TEST_METHOD(ConfigurationLoadTest) {
				Configuration config("Settings/Testing/ConfigurableTest1.json");
				config.Load();
				auto res = config.GetAttribute<std::string>("stringProperty");
				Assert::AreEqual(std::string("testString1"), res);
			}
			TEST_METHOD(ConfigurationGetAttributeTest) {
				Configuration config("Settings/Testing/ConfigurableTest2.json");
				config.Load();

				auto res = config.GetAttribute<std::string>("stringProperty");
				Assert::AreEqual(std::string("test2"), res);

				int res2 = config.GetAttribute<int>("integerProperty");
				Assert::AreEqual(2, res2);

				auto res3 = config.GetAttribute<float>("floatProperty");
				Assert::AreEqual(2.0f, res3, std::numeric_limits<float>::epsilon());

				auto res4 = config.GetAttribute<std::string>("propertyThatIsntThere");
				Assert::AreEqual(std::string(), res4);
			}

			TEST_METHOD(LoadErrorScriptTest) {
				Configuration config("Nonsense");
				config.Load();

				auto res = config.GetAttribute<bool>("Error");

				Assert::IsTrue(res);
			}
		};

}