//STD Headers
#include <fstream>

//Library Headers
#include "stdafx.h"
#include "CppUnitTest.h"

//Void Engine Headers
#include "ResourceManager.h"
#include "ThreadPool.h"
#include "Configuration.h"




using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace EngineUtils;

namespace EngineTestSuite {

	TEST_CLASS(ConfigurationResourceTests) {
		TEST_METHOD(ConfigurationLoadTest) {
			Configuration config("Settings/Testing/ConfigurableTest1.lua");
			config.Load();
			//auto res = config.GetAttribute<std::string>("stringProperty");
			//Assert::AreEqual(std::string("test1"), res);
		}
	};

}