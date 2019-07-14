//STD Headers
#include <fstream>

//Library Headers
#include "stdafx.h"
#include "CppUnitTest.h"

//Void Engine Headers
#include "ThreadPool.h"
#include "ResourceManager.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace EngineUtils;

namespace EngineTestSuite {
	TEST_CLASS(ResourceManagerTests) {
	public:
		struct RawFile : public Resource {
			const std::string ErrorString = "Error";
			std::string FileContents;

			RawFile(std::string path) : Resource(path) {

			}

			bool Load() override {
				std::ifstream ifs;
				ifs.open(ResourcePath);

				if (!ifs.is_open()) {
					FileContents = ErrorString;
				}
				else {
					std::getline(ifs, FileContents);
				}

				return true;
			}
		};

		TEST_METHOD(LoadNewResourceTest) {
			std::string SuccessString = "Wowza engine programming is fuckin' hard dude";

			std::shared_ptr<ThreadPool> pool = std::make_shared<ThreadPool>();
			ResourceManager resourceMan(pool);

			ResourceHandle handle =
				resourceMan.LoadResource<RawFile>("Resources/Testing/ResourceManagerDummyResource.txt");

			auto raw = handle.GetResource<RawFile>();
			
			Assert::AreEqual(SuccessString, raw->FileContents);
		}

		TEST_METHOD(RequestLoadedResourceTest) {
			Assert::Fail();
		}
	};
}