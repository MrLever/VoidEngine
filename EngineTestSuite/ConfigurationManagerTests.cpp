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

	TEST_CLASS(ConfigurationTests) {
		TEST_METHOD(ConfigurationLoadTest) {
			Configuration config("Settings/Testing/ConfigurableTest1.lua");
		}
	};

}