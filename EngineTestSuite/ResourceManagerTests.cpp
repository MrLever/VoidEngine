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
		TEST_METHOD(LoadFreshResourceTest) {
			std::string SuccessString = "Wow engine programming is fuckin' hard";

			struct RawFile : public Resource {
				const std::string ErrorString = "Error";
				std::string FileContents;

				RawFile(std::string path) : Resource(path) {

				}

				void Load() override {
					std::ifstream ifs;
					ifs.open(ResourcePath);

					if (!ifs.is_open()) {
						FileContents = ErrorString;
					}
					else {
						ifs >> FileContents;
					}
				}

			};

			std::shared_ptr<ThreadPool> pool = std::make_shared<ThreadPool>();
			ResourceManager resourceMan(pool);

			ResourceHandle handle =
				resourceMan.LoadResource<RawFile>("Resources/Testing/ResourceManagerDummyResource.txt");

			auto raw = handle.GetResource<RawFile>();
			
			//Assert::AreEqual(SuccessString, raw->FileContents);
		}
	};
}