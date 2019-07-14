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
					return false;
				}

				std::getline(ifs, FileContents);
				return true;
			}

			bool LoadErrorResource() override {
				FileContents = ErrorString;
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
			std::string SuccessString = "Wowza engine programming is fuckin' hard dude";

			std::shared_ptr<ThreadPool> pool = std::make_shared<ThreadPool>();
			ResourceManager resourceMan(pool);

			//Request resource to be loaded.
			auto dummyReq = 
				resourceMan.LoadResource<RawFile>("Resources/Testing/ResourceManagerDummyResource.txt");

			//Request resource be loaded again
			ResourceHandle handle =
				resourceMan.LoadResource<RawFile>("Resources/Testing/ResourceManagerDummyResource.txt");

			auto raw = handle.GetResource<RawFile>();

			Assert::AreEqual(SuccessString, raw->FileContents);
		}

		TEST_METHOD(RequestInvalidResourceTest) {
			std::string SuccessString = "Error";
			std::shared_ptr<ThreadPool> pool = std::make_shared<ThreadPool>();
			ResourceManager resourceMan(pool);

			auto invalidRequest = resourceMan.LoadResource<RawFile>("FooBar");
			Assert::AreEqual(SuccessString, invalidRequest.GetResource<RawFile>()->FileContents);
		}
	};
}